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

#include <stdio.h>

#include "decompress.hpp"

decompress::decompress() {

}

uint32_t decompress::translate(uint32_t instcode) {
    uint32_t ret = 0;
    uint8_t  op = instcode & 0x3;
    uint8_t  funct3 = (instcode >> 13) & 0x07;

    if (op == 3) {
        return instcode;        // not compressed instcode, return directly
    }
    // Compressed Instruction
    uint8_t  CI_rd =  (instcode >> 7) & 0x1f;
    uint8_t  CI_rs1 = CI_rd;
    uint32_t nzimm = 0;
    nzimm |= (instcode & 0x1000) >> 7;
    nzimm |= (instcode & 0x7c) >> 2;
    nzimm = sign_extend(nzimm, 5);

    switch ((funct3 << 2) | op) {
        case 0x1:              // 000_01: CI c.nop
            ret = encoder_itype(nzimm, CI_rs1, funct3, CI_rd, 0b0010011);
            break;
        default:
            printf("[Decompressed] error instruction %x...%x\n", funct3, op);
            break;
    }

    return ret;
}

// sign extend from specific position to MSB
uint32_t decompress::sign_extend(uint32_t x, uint8_t sign_position)
{
    uint32_t sign = (x >> sign_position) & 1;
    for (uint8_t i = sign_position + 1; i < 32; ++i)
        x |= sign << i;
    return x;
}

uint32_t decompress::encoder_itype(uint32_t imm, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode) {
    uint32_t inst = 0;
    inst |= imm << 20;
    inst |= rs1 << 15;
    inst |= funct3 << 12;
    inst |= rd << 7;
    inst |= opcode;
    return inst;
}