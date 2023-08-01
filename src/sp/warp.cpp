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

#include "warp.hpp"
#include "common/regid.hpp"

warp::warp(register_file *reg) {
    m_reg = reg;
    m_dec = new dec();
}

void warp::setup(message msg) {
    pc = msg.shader;
    // m_warp->setup_shader(shader);
    // write stack_pointer to sp
    // m_reg->write_ireg(0, 2, stack_pointer);
    // write arg1 to a0
    printf("setup ra: 0x0\n");
    printf("setup sp: 0x%lx\n", msg.stack_pointer);
    printf("setup a0: 0x%lx\n", msg.layout);
    printf("setup a1: 0x%x\n", msg.start);
    m_reg->write_ireg<uint64_t>(0, uint64_t(reg::ra), 0);
    m_reg->write_ireg<uint64_t>(0, uint64_t(reg::sp), msg.stack_pointer);
    m_reg->write_ireg<uint64_t>(0, uint64_t(reg::a0), msg.layout);
    m_reg->write_ireg<uint64_t>(0, uint64_t(reg::a1), msg.start);
}

inst_issue warp::schedule() {
    uint32_t instcode = *((uint32_t *)pc);
    inst_issue to_issue = m_dec->decode_inst(instcode);

    if (to_issue.type == encoding::INST_TYPE_BRANCH) {
        pc = branch(to_issue);

        to_issue.rs1 = m_reg->read_ireg(0, to_issue.rs1_id);
        to_issue.rs2 = m_reg->read_ireg(0, to_issue.rs2_id);
        to_issue.rs3 = m_reg->read_ireg(0, to_issue.rs3_id);

        pc = branch(to_issue);
        to_issue.type = encoding::INST_TYPE_NOP;
    } else {
        pc = pc + 4;
    }

    return to_issue;
}

uint64_t warp::branch(inst_issue inst) {
    uint64_t retpc = pc + 4;
    switch (inst.code) {
        case encoding::INST_BRANCH_AUIPC: {
            m_reg->write_ireg<uint64_t>(0, inst.rd, (pc + inst.u_imm));
            retpc = pc + 4;
            break;
        }
        case encoding::INST_BRANCH_BEQ: {
            if (inst.rs1 == inst.rs2) {
                retpc = pc + inst.sb_imm;
            } else {
                retpc = pc + 4;
            }
            printf("[EXEC.BRANCH.BEQ] jump to %lx, (%lx == %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BGEU: {
            printf("TODO BGEU\n");
            break;
        }
        case encoding::INST_BRANCH_BLTU: {
            if (inst.rs1< inst.rs2) {
                retpc = pc + inst.sb_imm;
            } else {
                retpc = pc + 4;
            }
            printf("[EXEC.BRANCH.BLTU] jump to %lx, (%lx == %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BNE: {
            printf("TODO BNE\n");
            break;
        }
        case encoding::INST_BRANCH_JAL: {
            m_reg->write_ireg<uint64_t>(0, inst.rd, pc + 4);
            retpc = (pc + inst.uj_imm);
            printf("[EXEC.BRANCH.JAL] jump to %lx\n", retpc);
            break;
        }
        case encoding::INST_BRANCH_JALR: {
            m_reg->write_ireg<uint64_t>(0, inst.rd, pc + 4);
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
