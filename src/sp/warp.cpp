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
#include <cassert>

#include "common/utils.hpp"
#include "common/regid.hpp"
#include "warp.hpp"

warp::warp(register_file *reg) {
    m_reg = reg;
    m_dec = new dec();
}

void warp::setup(message msg) {
    pc = msg.shader.pointer;
    startpc = msg.shader.pointer;
    lanes.reset();
    stops.set();

    printf("WARP Start from %d to %d\n", msg.start, msg.start + msg.count);
    for (uint32_t i=0; i<WARP_THREAD_N; i++) {
        if (i < msg.count) {
            lanes.set(i);
            stops.reset(i);

            m_reg->write_ireg(i, uint64_t(reg::s0), 0);
            m_reg->write_ireg(i, uint64_t(reg::ra), 0);

            printf("[SP][WARP0.%d] setup sp: 0x%lx\n", i, msg.shader.stack_pointer + 0x1000 * i);
            m_reg->write_ireg(i, uint64_t(reg::sp), msg.shader.stack_pointer + 0x1000 * i);

            printf("[SP][WARP0.%d] setup a0(tid): 0x%x\n", i, msg.start + i);
            m_reg->write_ireg(i, uint64_t(reg::a0), msg.start + i);
            for (uint32_t argi=1; argi<msg.shader.argsize; argi++) {
                printf("[SP][WARP0.%d] setup a%d(arg[%d]): 0x%lx\n", i, argi, argi, msg.shader.args[argi]);
                m_reg->write_ireg(i, uint64_t(reg::a0) + argi, msg.shader.args[argi]);
            }
        }
    }

    printf("[SP][WARP0] setup lanes: %lx\n", lanes.to_ulong());
    printf("[SP][WARP0] setup stops: %lx\n", stops.to_ulong());
}

inst_issue warp::schedule() {
    uint32_t instcode = *((uint32_t *)pc);
    printf("Fetch inst: [%lx (0x%lx)] 0x%08x\n", (uint64_t(pc) - uint64_t(startpc)), pc, instcode);
    inst_issue to_issue = m_dec->decode_inst(instcode);
    to_issue.lanes = lanes.to_ulong();

    if (to_issue.type == encoding::INST_TYPE_BRANCH) {
        FOREACH_WARP_THREAD {
            if (lanes.test(thread)) {
                npc[thread] = branch(to_issue, thread);
            }
        }

        struct warpstore torun = diverage();
        lanes = torun.lanes;
        pc = torun.pc;
        to_issue.type = encoding::INST_TYPE_NOP;
        to_issue.lanes = lanes.to_ulong();
    } else {
        pc = pc + 4;
    }

    return to_issue;
}

warpstore warp::diverage() {
    warpstore split0 = {0};
    warpstore split1 = {0};
    warpstore pop = {0};

    FOREACH_WARP_THREAD {
        if (lanes.test(thread)) {
            if ((pc + 4) != npc[thread]) {
                split1.pc = npc[thread];
                split1.lanes.set(thread);
            } else {
                split0.pc = npc[thread];
                split0.lanes.set(thread);
            }
        }
    }

    if (!warpstack.empty()) {
        pop = warpstack.top();
        warpstack.pop();
    }

    if (merge_lanes(split0, split1)) {
        if (merge_lanes(split0, pop)) {
            return split0;
        } else {
            warpstack.push(pop);
            return split0;
        }
    } else if (merge_lanes(split0, pop)) {
        warpstack.push(split1);
        return split0;
    } else if (merge_lanes(split1, pop)) {
        warpstack.push(split0);
        return split1;
    } else {
        warpstack.push(pop);
        warpstack.push(split1);
        return split0;
    }
}

bool warp::merge_lanes(struct warpstore &w0, struct warpstore &w1) {
    auto stopflip = stops;
    stopflip.flip();

    if (w0.lanes.none()) {
        w0.lanes = w1.lanes;
        w0.pc = w1.pc;

        return true;
    }

    if (w1.lanes.none()) {
        return true;
    }

    if (w0.pc == w1.pc) {
        w0.lanes = w0.lanes.operator|=(w1.lanes);
        w0.lanes = w0.lanes.operator&=(stopflip);
        return true;
    } else {
        return false;
    }
}

uint64_t warp::branch(inst_issue inst, uint32_t tid) {
    uint64_t retpc = pc + 4;
    inst.rs1 = m_reg->read_ireg(tid, inst.rs1_id);
    inst.rs2 = m_reg->read_ireg(tid, inst.rs2_id);
    inst.rs3 = m_reg->read_ireg(tid, inst.rs3_id);

    switch (inst.code) {
        case encoding::INST_BRANCH_AUIPC: {
            m_reg->write_ireg(tid, inst.rd, (pc + inst.u_imm));
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
        case encoding::INST_BRANCH_BGE: {
            if (int64_t(inst.rs1) >= int64_t(inst.rs2)) {
                retpc = pc + inst.sb_imm;
            } else {
                retpc = pc + 4;
            }
            printf("[EXEC.BRANCH.BGE] jump to %lx, if (%ld >= %ld)\n", retpc, inst.rs1, inst.rs2);
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
            m_reg->write_ireg(tid, inst.rd, pc + 4);
            retpc = (pc + inst.uj_imm);
            printf("[EXEC.BRANCH.JAL] jump to %lx\n", retpc);
            break;
        }
        case encoding::INST_BRANCH_JALR: {
            m_reg->write_ireg(tid, inst.rd, pc + 4);
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
    if (stops.all()) {
        return true;
    }

    if (pc == 0) {
        if (warpstack.empty()) {
            return true;
        } else {
            warpstore torun = warpstack.top();
            warpstack.pop();
            lanes = torun.lanes;
            pc = torun.pc;
            return false;
        }
    }

    return false;
}
