/*
 * Copyright © 2023 Sietium Semiconductor.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <cstdio>

#include "common/utils.hpp"
#include "common/regid.hpp"
#include "warp.hpp"

warp::warp(register_file *reg) {
    m_reg = reg;
    m_dec = new dec();
}

void warp::setup(message msg) {
    pc = msg.shader;
    startpc = msg.shader;

    for (uint32_t i=0; i<WARP_THREAD_N; i++) {
        if (i < msg.count) {
            lanes.set();
            stops.reset();
        } else {
            lanes.reset();
            stops.set();
        }
    }

    printf("[WARP] start lanes: %lx\n", lanes.to_ulong());
    printf("[WARP] start stops: %lx\n", stops.to_ulong());

    for (uint32_t i=0; i<WARP_THREAD_N; i++) {
        if (lanes.test(i)) {
            printf("[SP][WARP0.%d] setup ra: 0x0\n", i);
            printf("[SP][WARP0.%d] setup sp: 0x%lx\n", i, msg.stack_pointer + 0x1000 * i);
            printf("[SP][WARP0.%d] setup a0: 0x%lx\n", i, msg.layout);
            printf("[SP][WARP0.%d] setup a1: 0x%x\n", i, msg.start);

            m_reg->write_ireg<uint64_t>(i, uint64_t(reg::s0), 0);
            m_reg->write_ireg<uint64_t>(i, uint64_t(reg::ra), 0);
            m_reg->write_ireg<uint64_t>(i, uint64_t(reg::sp), msg.stack_pointer + 0x1000 * i);
            m_reg->write_ireg<uint64_t>(i, uint64_t(reg::a0), msg.layout);
            m_reg->write_ireg<uint64_t>(i, uint64_t(reg::a1), msg.start + i);
        }
    }
}

inst_issue warp::schedule() {
    uint32_t instcode = *((uint32_t *)pc);
    printf("Fetch inst 0x%08x\n", instcode);
    inst_issue to_issue = m_dec->decode_inst(instcode);
    to_issue.lanes = lanes.to_ulong();

    if (to_issue.type == encoding::INST_TYPE_BRANCH) {
        FOREACH_WARP_THREAD {
            if (lanes.test(thread)) {
                npc[thread] = branch(to_issue, thread);
            }
        }

        pc = diverage();
        to_issue.type = encoding::INST_TYPE_NOP;
    } else {
        pc = pc + 4;
    }

    return to_issue;
}

uint64_t warp::diverage() {
    uint64_t rpc;
    bool notall = false;

    uint64_t next = pc + 4;
    uint64_t next_t = next;
    FOREACH_WARP_THREAD {
        if (lanes.test(thread)) {
            if (next != npc[thread]) {
                next_t = npc[thread];
            } else {
                notall = true;
            }
        }
    }

    if (next_t == next) {  // all thread jump to next instruction
        rpc = next;
    } else if (next_t == 0) {  // some thread will stop
        FOREACH_WARP_THREAD {
            if (lanes.test(thread)) {
                lanes.reset(thread);
                stops.set(thread);
            }
        }

        rpc = stops.all() ? 0: next;
    } else if (notall) {
        rpc = next;
    } else {
        rpc = next_t;
    }

    printf("diverge lanes: %lx\n", lanes.to_ulong());
    printf("diverge stops: %lx\n", stops.to_ulong());
    return rpc;
}

uint64_t warp::branch(inst_issue inst, uint32_t tid) {
    uint64_t retpc = pc + 4;
    inst.rs1 = m_reg->read_ireg(tid, inst.rs1_id);
    inst.rs2 = m_reg->read_ireg(tid, inst.rs2_id);
    inst.rs3 = m_reg->read_ireg(tid, inst.rs3_id);

    switch (inst.code) {
        case encoding::INST_BRANCH_AUIPC: {
            m_reg->write_ireg<uint64_t>(tid, inst.rd, (pc + inst.u_imm));
            retpc = pc + 4;
            break;
        }
        case encoding::INST_BRANCH_BEQ: {
            if (inst.rs1 == inst.rs2) {
                retpc = pc + inst.sb_imm;
            } else {
                retpc = pc + 4;
            }
            printf("[EXEC.BRANCH.BEQ] jump to %lx, if (%lx == %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BGEU: {
            if (inst.rs1 >= inst.rs2) {
                retpc = pc + inst.sb_imm;
            } else {
                retpc = pc + 4;
            }
            printf("[EXEC.BRANCH.BGEU] jump to %lx, if (%lx >= %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BLTU: {
            if (inst.rs1 < inst.rs2) {
                retpc = pc + inst.sb_imm;
            } else {
                retpc = pc + 4;
            }
            printf("[EXEC.BRANCH.BLTU] jump to %lx, if (%lx < %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BNE: {
            if (inst.rs1 != inst.rs2) {
                retpc = pc + inst.sb_imm;
            } else {
                retpc = pc + 4;
            }
            printf("[EXEC.BRANCH.BNE] jump to %lx, if (%lx != %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_JAL: {
            m_reg->write_ireg<uint64_t>(tid, inst.rd, pc + 4);
            retpc = (pc + inst.uj_imm);
            printf("[EXEC.BRANCH.JAL] jump to %lx\n", retpc);
            break;
        }
        case encoding::INST_BRANCH_JALR: {
            m_reg->write_ireg<uint64_t>(tid, inst.rd, pc + 4);
            retpc = (inst.rs1 + inst.i_imm) & ~(uint64_t)(1);
            printf("[EXEC.BRANCH.JALR] jump to %lx\n", retpc);
            break;
        }
        default:
            printf("BRANCH INST TODO!\n");
            break;
    }

    return retpc;
}

bool warp::stop() {
    return pc != 0;
}
