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

// reference: https://github.com/kaeteyaruyo/rv32emu-next.git
// instruction decode masks
enum {
    //                ....xxxx....xxxx
    C_RD          = 0b0000111110000000, // general
    C_RS1         = 0b0000111110000000,
    C_RS2         = 0b0000000001111100,
    C_RD_S        = 0b0000000000011100,
    C_RS1_S       = 0b0000001110000000,
    C_RS2_S       = 0b0000000000011100,
    //                ....xxxx....xxxx
    CR_FUNCT4     = 0b1111000000000000, // CR-format
    //                ....xxxx....xxxx
    CI_MASK_12    = 0b0001000000000000, // CI-format
    CI_MASK_6_4   = 0b0000000001110000,
    CI_MASK_3_2   = 0b0000000000001100,
    //                ....xxxx....xxxx
    CSS_IMM_5_2   = 0b0001111000000000, // CSS-format
    CSS_IMM_7_6   = 0b0000000110000000,
    //                ....xxxx....xxxx
    CIW_IMM_5_4   = 0b0001100000000000, // CIW-format
    CIW_IMM_9_6   = 0b0000011110000000,
    CIW_IMM_2     = 0b0000000001000000,
    CIW_IMM_3     = 0b0000000000100000,
    //                ....xxxx....xxxx
    CLWSW_IMM_5_3 = 0b0001110000000000, // C.LW, C.SW
    CLWSW_IMM_2   = 0b0000000001000000,
    CLWSW_IMM_6   = 0b0000000000100000,
    CLDSD_IMM_7_6 = 0b0000000001100000,
    //                ....xxxx....xxxx
    CS_FUNCT6     = 0b1111110000000000, // CS-format
    CS_FUNCT2     = 0b0000000001100000,
    //                ....xxxx....xxxx
    CB_FUNCT2     = 0b0000110000000000, // C.SRLI, C.SRAI, C.ANDI
    CB_OFFSET_8   = 0b0001000000000000, // C.BEQZ, C.BNEZ
    CB_OFFSET_4_3 = 0b0000110000000000,
    CB_OFFSET_7_6 = 0b0000000001100000,
    CB_OFFSET_2_1 = 0b0000000000011000,
    CB_OFFSET_5   = 0b0000000000000100,
    //                ....xxxx....xxxx
    CJ_OFFSET_11  = 0b0001000000000000, // CJ-format
    CJ_OFFSET_4   = 0b0000100000000000,
    CJ_OFFSET_9_8 = 0b0000011000000000,
    CJ_OFFSET_10  = 0b0000000100000000,
    CJ_OFFSET_6   = 0b0000000010000000,
    CJ_OFFSET_7   = 0b0000000001000000,
    CJ_OFFSET_3_1 = 0b0000000000111000,
    CJ_OFFSET_5   = 0b0000000000000100,
};

#define _BITS(pos, width)   (((instcode) >> (pos)) & ((1ULL << (width)) - 1ULL))

decompress::decompress() {

}

uint32_t decompress::translate(uint32_t instcode) {
    uint32_t ret = 0;
    uint8_t  op = instcode & 0x3;
    uint8_t  funct3 = (instcode >> 13) & 0x07;

    if (op == 3) {
        return instcode;        // not compressed instcode, return directly
    }

    // Command bits
    uint8_t  C_rd       = dec_rd(instcode);
    uint8_t  C_rs1      = C_rd;
    uint8_t  C_rs2      = dec_rs2(instcode);
    // 3-bit short register, need mapping to  to a0~a8, so need to or 0b1000
    uint8_t  C_rds      = (C_rd & 0b0111) | 0b1000;
    uint8_t  C_rs1s     = C_rds;
    uint8_t  C_rs2s     = (C_rs2 & 0b0111) | 0b1000;

    // CI type: Immediate
    uint32_t CI_uimm    = dec_ci_uimm(instcode);
    uint32_t CI_imm94   = dec_ci_imm94(instcode);
    uint32_t CI_imm     = sign_extend(CI_uimm, 5);

    // CJ type: Jump
    uint32_t CJ_imm     = dec_cj_imm(instcode);
    uint32_t CB_imm     = dec_branch_imm(instcode);

    // CIW type
    uint32_t CIW_imm    = dec_ciw_imm(instcode);

    // CL type
    uint32_t CLW_imm    = dec_clsw_imm(instcode);
    uint32_t CLD_imm    = dec_clsd_imm(instcode);

    // CSS type
    uint32_t CSS_limmd   = (_BITS(12, 1) << 5) | (_BITS(5, 2) << 3) | (_BITS(2, 3) << 6);
    uint32_t CSS_limm    = (_BITS(12, 1) << 5) | (_BITS(4, 3) << 2) | (_BITS(2, 2) << 6);
    uint32_t CSS_simmd   = (_BITS(10, 3) << 3) | (_BITS(7, 3) << 6);
    uint32_t CSS_simm    = (_BITS(9, 4) << 2) | (_BITS(7, 2) << 6);

    // TODO. decoder with search table
    // f3  op
    // xxx_xx
    switch ((funct3 << 2) | op) {
        /* bit[1:0] = 0b01 */
        case 0b00001: { // 000_01: CI c.nop and c.addi. c.nop is: c.addi x0, x0, 0
            ret = encode_itype(CI_imm, C_rs1, funct3, C_rd, 0b0010011);
            break;
        }
        case 0b00101: { // 001_01: CJ c.jal, jal x1, offset[11:1]
            ret = encode_jtype(CJ_imm, 1, 0b1101111);
            break;
        }
        case 0b01001: {
            // 010_01: CI c.li, convert to addi rd, x0, imm[5:0]
            ret = encode_itype(CI_imm, 0, 0b000, C_rd, 0b0010011);
            break;
        }
        case 0b01101: {
            // 011_01: CI c.addi16sp and c.lui
            // c.addi16sp  ==>  addi x2, x2, CI_imm94
            // c.lui       ==>  addi CI_rd, x0, CI_imm    or convert to LUI (TODO. which one is more convenient?)
            CI_imm = (C_rd == 2) ? CI_imm94 : CI_imm;
            C_rs1 = (C_rd == 2) ? C_rd : 0;
            ret = encode_itype(CI_imm, C_rs1, 0b000, C_rd, 0b0010011);
            break;
        }
        case 0b10001: {
            uint8_t rd = C_rd >> 3;
            switch (rd) {
                case 0b00:  // c.srli
                    ret = encode_itype(CI_uimm, C_rs1s, 0b101, C_rds, 0b0010011);
                    break;
                case 0b01:  // c.srai
                    ret = encode_itype(CI_uimm | 0x400, C_rs1s, 0b101, C_rds, 0b0010011);
                    break;
                case 0b10:  // c.andi
                    ret = encode_itype(CI_imm, C_rs1s, 0b111, C_rds, 0b0010011);
                    break;
                case 0b11: { // R-type  c.sub, c.xor, c.or, c.and
                    uint8_t sel = ((C_rs2 >> 3) & 0b11);
                    if (sel == 0b00) {
                        ret = encode_rtype(0b0100000, C_rs2s, C_rs1s, 0b000, C_rds, 0b0110011); // c.sub
                    } else if (sel == 0b01) {
                        ret = encode_rtype(0b0000000, C_rs2s, C_rs1s, 0b100, C_rds, 0b0110011); // c.xor
                    } else if (sel == 0b10) {
                        ret = encode_rtype(0b0000000, C_rs2s, C_rs1s, 0b110, C_rds, 0b0110011); // c.or
                    } else if (sel == 0b11) {
                        ret = encode_rtype(0b0000000, C_rs2s, C_rs1s, 0b111, C_rds, 0b0110011); // c.and
                    } else {
                        printf("encoding error\n");
                    }
                    break;
                }
                default:
                    printf("TODO decompress\n");
                    break;
             }
            break;
        }
        case 0b10101: { // c.j
            ret = encode_jtype(CJ_imm, 0, 0b1101111);
            break;
        }
        case 0b11001: { // c.beqz  ==> beq rs1', x0, offset[8:1]
            ret = encode_btype(CB_imm, 0, C_rs1s, 0b000, 0b1100011);
            break;
        }
        case 0b11101: { // c.bnez  ==> bne rs1', x0, offset[8:1]
            ret = encode_btype(CB_imm, 0, C_rs1s, 0b001, 0b1100011);
            break;
        }
        /* bit[1:0] = 0b00 */
        case 0b00000: { // 000_00: c.addi4spn  ==> addi rd' x2 nzuimm[9:2]
            ret = encode_itype(CIW_imm, 2, 0b000, C_rs2s, 0b0010011);
            break;
        }
        case 0b00100: { // c.fld ==>
            ret = encode_itype(CLD_imm, C_rs1s, 0b011, C_rs2s, 0b0000111);
            break;
        }
        case 0b01000: { // c.lw
            ret = encode_itype(CLW_imm, C_rs1s, 0b010, C_rs2s, 0b0000011);
            break;
        }
        case 0b01100: { // c.flw
            ret = encode_itype(CLW_imm, C_rs1s, 0b010, C_rs2s, 0b0000111);
            break;
        }
        case 0b10100: { // c.fsd
            ret = encode_stype(CLD_imm, C_rs2s, C_rs1s, 0b011, 0b0100111);
            break;
        }
        case 0b11000: { // c.sw
            ret = encode_stype(CLW_imm, C_rs2s, C_rs1s, 0b010, 0b0100011);
            break;
        }
        case 0b11100: { // c.fsw
            ret = encode_stype(CLW_imm, C_rs2s, C_rs1s, 0b010, 0b0100111);
            break;
        }
        /* bit[1:0] = 0x10 */
        case 0b00010: { // 000_10: c.slli, c.slli64  ==> slli rd, rd, shamt[5:0]
            ret = encode_itype(CI_uimm, C_rs1, 0b001, C_rd, 0b0010011);
            break;
        }
        case 0b00110: { // 001_10: c.fldsp
            ret = encode_itype(CSS_limmd, 2, 0b011, C_rd, 0b0000111);
            break;
        }
        case 0b01010: { // 010_10: c.lwsp
            ret = encode_itype(CSS_limm, 2, 0b010, C_rd, 0b0000011);
            break;
        }
        case 0b01110: { // 011_10: c.flwsp
            ret = encode_itype(CSS_limm, 2, 0b010, C_rd, 0b0000111);
            break;
        }
        case 0b10010: { // 100_10: c.jr\c.mv\c.ebreak\c.jalr\c.add
            if (C_rs2 != 0) {
                uint8_t rs1 = _BITS(12, 1) ? C_rd : 0;
                ret = encode_rtype(0b0000000, C_rs2, rs1, 0b000, C_rd, 0b0110011);
            } else if (C_rd == 0) { // c.ebreak
                ret = encode_itype(1, 0, 0b000, 0, 0b1110011);
            } else {
                ret = encode_itype(0, C_rs1, 0b000, _BITS(12, 1), 0b1100111);
            }
            break;
        }
        case 0b10110: { // 101_10: c.fsdsp
            ret = encode_stype(CSS_simmd, C_rs2, 2, 0b011, 0b0100111);
            break;
        }
        case 0b11010: { // 110_10: c.swsp  ==> sw rs2, offset[7:2](x2)
            ret = encode_stype(CSS_simm, C_rs2, 2, 0b010, 0b0100011);
            break;
        }
        case 0b11110: { // 111_10: c.fswsp
            ret = encode_stype(CSS_simm, C_rs2, 2, 0b010, 0b0100111);
            break;
        }
        default:
            printf("[Decompressed] error instruction %x...%x\n", funct3, op);
            break;
    }

    return ret;
}

// sign extend from specific position to MSB
inline uint32_t decompress::sign_extend(uint32_t x, uint8_t sign_position)
{
    uint32_t sign = (x >> sign_position) & 1;
    for (uint8_t i = sign_position + 1; i < 32; ++i)
        x |= sign << i;
    return x;
}

// decode rd field
inline uint8_t decompress::dec_rd(uint16_t inst)
{
    return (inst & C_RD) >> 7;
}

// decode rs2 field
inline uint8_t decompress::dec_rs2(uint16_t inst)
{
    return (inst & C_RS2) >> 2;
}

// decode CI-format instruction immediate
inline uint32_t decompress::dec_ci_uimm(uint16_t inst) {
    uint32_t imm = 0;
    imm |= (inst & CI_MASK_12) >> 7;
    imm |= (inst & (CI_MASK_6_4 | CI_MASK_3_2)) >> 2;
    return imm;
}

// decode immediate of C.LW and C.SW
inline uint32_t decompress::dec_clsd_imm(uint16_t inst)
{
    // zero-extended offset, scaled by 4
    uint32_t imm = 0;
    imm |= (inst & CLDSD_IMM_7_6) << 1;
    imm |= (inst & CLWSW_IMM_5_3) >> 7;
    return imm;
}

// decode immediate of C.LW and C.SW
inline uint32_t decompress::dec_clsw_imm(uint16_t inst)
{
    // zero-extended offset, scaled by 4
    uint32_t imm = 0;
    imm |= (inst & CLWSW_IMM_6) << 1;
    imm |= (inst & CLWSW_IMM_5_3) >> 7;
    imm |= (inst & CLWSW_IMM_2) >> 4;
    return imm;
}

// decode CI-format instruction immediate[9:4]
inline uint32_t decompress::dec_ci_imm94(uint16_t inst) {
    // decode nzimm
    uint32_t imm94 = 0;
    imm94 |= (inst & 0x1000) >> 3;
    imm94 |= (inst & 0x0018) << 4;
    imm94 |= (inst & 0x0020) << 1;
    imm94 |= (inst & 0x0004) << 3;
    imm94 |= (inst & 0x0040) >> 2;
    imm94 = sign_extend(imm94, 9);
    return imm94;
}

// decode CJ-format instruction immediate
inline uint32_t decompress::dec_cj_imm(uint16_t inst) {
    // sign-extended offset, scaled by 2
    uint32_t imm = 0;
    imm |= (inst & CJ_OFFSET_11) >> 1;
    imm |= (inst & CJ_OFFSET_10) << 2;
    imm |= (inst & CJ_OFFSET_9_8) >> 1;
    imm |= (inst & CJ_OFFSET_7) << 1;
    imm |= (inst & CJ_OFFSET_6) >> 1;
    imm |= (inst & CJ_OFFSET_5) << 3;
    imm |= (inst & CJ_OFFSET_4) >> 7;
    imm |= (inst & CJ_OFFSET_3_1) >> 2;
    imm = sign_extend(imm, 11);
    return imm;
}

// decode immediate of branch instruction
inline uint32_t decompress::dec_branch_imm(uint16_t inst)
{
    // sign-extended offset, scaled by 2
    uint32_t imm = 0;
    imm |= (inst & CB_OFFSET_8) >> 4;
    imm |= (inst & CB_OFFSET_7_6) << 1;
    imm |= (inst & CB_OFFSET_5) << 3;
    imm |= (inst & CB_OFFSET_4_3) >> 7;
    imm |= (inst & CB_OFFSET_2_1) >> 2;
    imm = sign_extend(imm, 8);
    return imm;
}

// decode CIW-format instruction immediate
inline uint32_t decompress::dec_ciw_imm(uint16_t inst)
{
    // zero-extended non-zero immediate, scaled by 4
    uint32_t imm = 0;
    imm |= (inst & CIW_IMM_9_6) >> 1;
    imm |= (inst & CIW_IMM_5_4) >> 7;
    imm |= (inst & CIW_IMM_3) >> 2;
    imm |= (inst & CIW_IMM_2) >> 4;
    return imm;
}

inline uint32_t decompress::encode_itype(uint32_t imm, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode) {
    uint32_t inst = 0;
    inst |= imm << 20;
    inst |= rs1 << 15;
    inst |= funct3 << 12;
    inst |= rd << 7;
    inst |= opcode;
    return inst;
}

inline uint32_t decompress::encode_jtype(uint32_t imm, uint32_t rd, uint32_t opcode)
{
    uint32_t inst = 0;
    inst |= (imm & 0x00100000) << 11;
    inst |= (imm & 0x000007FE) << 20;
    inst |= (imm & 0x00000800) << 9;
    inst |= (imm & 0x000FF000);
    inst |= rd << 7;
    inst |= opcode;
    return inst;
}

inline uint32_t decompress::encode_rtype(uint32_t funct7, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode)
{
    uint32_t inst = 0;
    inst |= funct7 << 25;
    inst |= rs2 << 20;
    inst |= rs1 << 15;
    inst |= funct3 << 12;
    inst |= rd << 7;
    inst |= opcode;
    return inst;
}

inline uint32_t decompress::encode_btype(uint32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode)
{
    uint32_t inst = 0;
    inst |= (imm & 0b1000000000000) << 19;
    inst |= (imm & 0b0011111100000) << 20;
    inst |= rs2 << 20;
    inst |= rs1 << 15;
    inst |= funct3 << 12;
    inst |= (imm & 0b0000000011110) << 7;
    inst |= (imm & 0b0100000000000) >> 4;
    inst |= opcode;
    return inst;
}

inline uint32_t decompress::encode_stype(uint32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode)
{
    uint32_t inst = 0;
    inst |= (imm & 0b111111100000) << 20;
    inst |= rs2 << 20;
    inst |= rs1 << 15;
    inst |= funct3 << 12;
    inst |= (imm & 0b000000011111) << 7;
    inst |= opcode;
    return inst;
}