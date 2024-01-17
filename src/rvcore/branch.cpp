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

writeback_t branch::run(rvinst_issue inst, uint64_t &pc_increment) {
    writeback_t res = {};
    uint64_t pc = inst.currpc;
    uint8_t pc_step = IS_COMPRESSED_INST(inst.bits) ? 2 : 4;
    pc_increment = pc_step;
    switch (inst.code) {
        case encoding::INST_BRANCH_AUIPC: {
            res = writeback_t{inst.rd, (pc + inst.u_imm)};
            RVGPU_DEBUG_PRINT("[EXEC.AUIPC] r[%ld] = %lx\n", res.rid, res.wdata);
            break;
        }
        case encoding::INST_BRANCH_BEQ: {
            if (inst.rs1 == inst.rs2) {
                pc_increment = inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BEQ] jump to %lx, if (%lx == %lx)\n", pc + pc_increment, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BGE: {
            if (sreg_t(inst.rs1) >= sreg_t(inst.rs2)) {
                pc_increment = inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BGE] jump to %lx, if (%ld >= %ld)\n", pc + pc_increment, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BGEU: {
            if (inst.rs1 >= inst.rs2) {
                pc_increment = inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BGEU] jump to %lx, if (%lx >= %lx)\n", pc + pc_increment, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BLTU: {
            if (inst.rs1 < inst.rs2) {
                pc_increment = inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BLTU] jump to %lx, if (%lx < %lx)\n", pc + pc_increment, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BLT: {
            if (sreg_t(inst.rs1) < sreg_t(inst.rs2)) {
                pc_increment = inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BLT] jump to %lx, if (%lx < %lx)\n", pc + pc_increment, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_BNE: {
            if (inst.rs1 != inst.rs2) {
                pc_increment = inst.sb_imm;
            }
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.BNE] jump to %lx, if (%lx != %lx)\n", pc + pc_increment, inst.rs1, inst.rs2);
            break;
        }
        case encoding::INST_BRANCH_JAL: {
            pc_increment = inst.uj_imm;
            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.JAL] jump to %lx\n", pc + pc_increment);
            res = writeback_t {inst.rd, pc + pc_step};
            break;
        }
        case encoding::INST_BRANCH_JALR: {
            pc_increment = ((inst.rs1 + inst.i_imm) & ~(uint64_t)(1)) - pc;

            RVGPU_DEBUG_PRINT("[EXEC.BRANCH.JALR] jump to %lx\n", pc + pc_increment);
            res = writeback_t {inst.rd, pc + pc_step};
            break;
        }
        default:
            RVGPU_ERROR_PRINT("BRANCH INST TODO!\n");
            break;
    }

    return res;
}