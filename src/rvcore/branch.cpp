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

#include "common/debug.hpp"

#include "branch.hpp"
#include "encoding.hpp"

branch::branch() {

}

writeback_t branch::run(inst_issue inst, uint64_t &retpc) {
    writeback_t res = {0, 0};
    uint64_t pc = inst.currpc;
    retpc = pc + 4;

    switch (inst.code) {
        case encoding::INST_BRANCH_AUIPC: {
            res = writeback_t {inst.rd, (pc + inst.u_imm)};
            break;
        }
        case encoding::INST_BRANCH_BEQ: {
            if (inst.rs1 == inst.rs2) {
                retpc = pc + inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BEQ] jump to %lx, if (%lx == %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BGE: {
            if (sreg_t(inst.rs1) >= sreg_t(inst.rs2)) {
                retpc = pc + inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BGE] jump to %lx, if (%ld >= %ld)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BGEU: {
            if (inst.rs1 >= inst.rs2) {
                retpc = pc + inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BGEU] jump to %lx, if (%lx >= %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BLTU: {
            if (inst.rs1 < inst.rs2) {
                retpc = pc + inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BLTU] jump to %lx, if (%lx < %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BLT: {
            if (sreg_t(inst.rs1) < sreg_t(inst.rs2)) {
                retpc = pc + inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BLT] jump to %lx, if (%lx < %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BNE: {
            if (inst.rs1 != inst.rs2) {
                retpc = pc + inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BNE] jump to %lx, if (%lx != %lx)\n", retpc, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_JAL: {
            retpc = (pc + inst.uj_imm);
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.JAL] jump to %lx\n", retpc);
            res = writeback_t {inst.rd, pc + 4};
            break;
        }
        case encoding::INST_BRANCH_JALR: {
            retpc = (inst.rs1 + inst.i_imm) & ~(uint64_t)(1);
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.JALR] jump to %lx\n", retpc);
            res = writeback_t {inst.rd, pc + 4};
            break;
        }
        default:
            RVGPU_ERROR_PRINT("BRANCH INST TODO!\n");
            break;
    }

    return res;
}