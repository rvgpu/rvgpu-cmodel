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

#include <cstdlib>
#include <cstdio>

#include "stream_processor.hpp"
#include "encoding.hpp"

stream_processor::stream_processor() {
    m_reg = new register_file();
    m_alu = new alu();
    m_fpu = new fpu();
    m_warp = new warp(m_reg);
    m_ls = new load_store(m_reg);
}

void stream_processor::setup(message msg) {
    m_warp->setup(msg);
}

uint64_t stream_processor::execuator(inst_issue to_issue) {
    uint64_t result;
    uint64_t npc = 0;
    switch (to_issue.type) {
        case encoding::INST_TYPE_ALU: {
            to_issue.rs1 = m_reg->read_ireg(0, to_issue.rs1_id);
            to_issue.rs2 = m_reg->read_ireg(0, to_issue.rs2_id);
            to_issue.rs3 = m_reg->read_ireg(0, to_issue.rs3_id);
            result = m_alu->run(to_issue);
            npc = pc + 4;
            m_reg->write_ireg<uint64_t>(0, to_issue.rd, result);
            break;
        }
        case encoding::INST_TYPE_FPU: {
            to_issue.rs1 = m_reg->read_freg(0, to_issue.rs1_id);
            to_issue.rs2 = m_reg->read_freg(0, to_issue.rs2_id);
            to_issue.rs3 = m_reg->read_freg(0, to_issue.rs3_id);
            result = m_fpu->run(to_issue);
            m_reg->write_freg(0, to_issue.rd, result);
            npc = pc + 4;
            break;
        }
        case encoding::INST_TYPE_LS: {
            to_issue.rs1 = m_reg->read_ireg(0, to_issue.rs1_id);
            to_issue.rs2 = m_reg->read_ireg(0, to_issue.rs2_id);
            to_issue.rs3 = m_reg->read_ireg(0, to_issue.rs3_id);
            m_ls->run(to_issue);
            npc = pc + 4;
            break;
        }
        case encoding::INST_TYPE_NOP: {
            printf("Instruction NOP\n");
            break;
        }
        default:
            break;
    }

    return npc;
}

void stream_processor::run() {
    while (m_warp->stop()) {
        inst_issue to_issue = m_warp->schedule();

        pc = execuator(to_issue);
    }
}