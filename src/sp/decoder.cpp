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

#include "decoder.hpp"

using namespace encoding;

struct instlist {
    INST code;
    uint32_t match;
    uint32_t mask;
};

#define DECLARE_INSN_ALU(iname) {.code = INST_ALU_##iname, .match = MATCH_##iname, .mask = MASK_##iname}
#define DECLARE_INSN_FPU(iname) {.code = INST_FPU_##iname, .match = MATCH_##iname, .mask = MASK_##iname}
#define DECLARE_INSN_LS(iname)  {.code = INST_LS_##iname, .match = MATCH_##iname, .mask = MASK_##iname}
#define DECLARE_INSN_BRANCH(iname)  {.code = INST_BRANCH_##iname, .match = MATCH_##iname, .mask = MASK_##iname}

std::vector<struct instlist> insts = {
        DECLARE_INSN_ALU(ADD),
        DECLARE_INSN_ALU(ADDI),
        DECLARE_INSN_ALU(ADDIW),
        DECLARE_INSN_ALU(ADDW),
        DECLARE_INSN_BRANCH(AUIPC),
        DECLARE_INSN_BRANCH(BEQ),
        DECLARE_INSN_BRANCH(BGEU),
        DECLARE_INSN_BRANCH(BLTU),
        DECLARE_INSN_BRANCH(BNE),
        DECLARE_INSN_FPU(FMUL_S),
        DECLARE_INSN_LS(FLW),
        DECLARE_INSN_FPU(FMADD_S),
        DECLARE_INSN_FPU(FMUL_S),
        DECLARE_INSN_FPU(FMUL_S),
        DECLARE_INSN_LS(FSW),
        DECLARE_INSN_LS(LD),
        DECLARE_INSN_LS(LUI),
        DECLARE_INSN_LS(LW),
        DECLARE_INSN_LS(LWU),
        DECLARE_INSN_ALU(MUL),
        DECLARE_INSN_ALU(MULW),
        DECLARE_INSN_LS(SW),
        DECLARE_INSN_ALU(SLTU),
        DECLARE_INSN_ALU(SLLIW),
        DECLARE_INSN_ALU(SLLI),
        DECLARE_INSN_ALU(SLT),
        DECLARE_INSN_BRANCH(JAL),
        DECLARE_INSN_BRANCH(JALR),
        DECLARE_INSN_LS(SD),
        DECLARE_INSN_ALU(ANDI),
        DECLARE_INSN_ALU(ORI),
        DECLARE_INSN_ALU(XORI),
        DECLARE_INSN_ALU(OR),
};

dec::dec() {

}

inst_issue dec::decode_inst(uint32_t instcode) {
    inst_issue to_issue;

    to_issue.bits = instcode;
    to_issue.code = match(instcode);
    to_issue.type = to_issue.code & encoding::INST_TYPE_MASK;

    bits = instcode;
    to_issue.rd = xget(7, 5);
    to_issue.rs1_id = xget(15, 5);
    to_issue.rs2_id = xget(20, 5);
    to_issue.rs3_id = xget(27, 5);

    to_issue.u_imm = int64_t(xsget(12, 20) << 12);
    to_issue.i_imm = int64_t(xsget(20, 12));
    to_issue.s_imm = xget(7, 5) + (xsget(25, 7) << 5);
    to_issue.sb_imm = (xget(8, 4) << 1) + (xget(25, 6) << 5) + (xget(7, 1) << 11) + (imm_sign() << 12);
    to_issue.uj_imm = (xget(21, 10) << 1) + (xget(20, 1) << 11) + (xget(12, 8) << 12) + (imm_sign() << 20);

    return to_issue;
}

encoding::INST dec::match(uint32_t instcode) {
    for (auto iter : insts) {
        if ((instcode & iter.mask) == iter.match) {
            return iter.code;
        }
    }

    return encoding::INST_ERROR_CODE;
}