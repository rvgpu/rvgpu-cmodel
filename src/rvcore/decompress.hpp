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

#pragma once
#include <cstdint>

class decompress {
public:
    decompress();

    uint32_t translate(uint32_t instcode);

private:
    uint32_t encode_itype(uint32_t imm, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode);
    uint32_t encode_jtype(uint32_t imm, uint32_t rd, uint32_t opcode);
    uint32_t encode_rtype(uint32_t funct7, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode);
    uint32_t encode_btype(uint32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode);
    uint32_t encode_stype(uint32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode);

    uint32_t dec_branch_imm(uint16_t inst);
    uint32_t dec_cj_imm(uint16_t inst);
    uint32_t dec_ciw_imm(uint16_t inst);
    uint32_t dec_clsw_imm(uint16_t inst);
    uint32_t dec_clsd_imm(uint16_t inst);
};