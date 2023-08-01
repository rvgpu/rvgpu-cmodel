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
#include <vector>

namespace encoding {

#define MATCH_ADD 0x33
#define MASK_ADD 0xfe00707f
#define MATCH_ADDI 0x13
#define MASK_ADDI 0x707f
#define MATCH_ADDIW 0x1b
#define MASK_ADDIW 0x707f
#define MATCH_ADDW 0x3b
#define MASK_ADDW 0xfe00707f
#define MATCH_AUIPC 0x17
#define MASK_AUIPC 0x7f
#define MATCH_BEQ 0x63
#define MASK_BEQ 0x707f
#define MATCH_BGEU 0x7063
#define MASK_BGEU 0x707f
#define MATCH_BLTU 0x6063
#define MASK_BLTU 0x707f
#define MATCH_BNE 0x1063
#define MASK_BNE 0x707f
#define MATCH_FADD_S 0x53
#define MASK_FADD_S 0xfe00007f
#define MATCH_FLW 0x2007
#define MASK_FLW 0x707f
#define MATCH_FMADD_S 0x43
#define MASK_FMADD_S 0x0600007f
#define MATCH_FMUL_S 0x10000053
#define MASK_FMUL_S 0xfe00007f
#define MATCH_FDIV_S 0x18000053
#define MASK_FDIV_S 0xfe00007f
#define MATCH_FSW 0x2027
#define MASK_FSW 0x707f
#define MATCH_LD 0x3003
#define MASK_LD 0x707f
#define MATCH_LUI 0x37
#define MASK_LUI 0x7f
#define MATCH_LW 0x2003
#define MASK_LW 0x707f
#define MATCH_LWU 0x6003
#define MASK_LWU 0x707f
#define MATCH_MUL 0x02000033
#define MASK_MUL 0xfe00707f
#define MATCH_MULW 0x0200003b
#define MASK_MULW 0xfe00707f
#define MATCH_SW 0x2023
#define MASK_SW 0x707f
#define MATCH_SLTU 0x3033
#define MASK_SLTU 0xfe00707f
#define MATCH_SLLIW 0x101b
#define MASK_SLLIW 0xfe00707f
#define MATCH_SLLI 0x1013
#define MASK_SLLI 0xfc00707f
#define MATCH_SLT 0x2033
#define MASK_SLT 0xfe00707f
#define MATCH_JAL 0x6f
#define MASK_JAL 0x7f
#define MATCH_JALR 0x67
#define MASK_JALR 0x707f
#define MATCH_SD 0x3023
#define MASK_SD 0x707f
#define MATCH_SRLI 0x5013
#define MASK_SRLI 0xfc00707f
#define MATCH_ANDI 0x7013
#define MASK_ANDI 0x707f
#define MATCH_ORI 0x6013
#define MASK_ORI 0x707f
#define MATCH_XORI 0x4013
#define MASK_XORI 0x707f
#define MATCH_OR 0x6033
#define MASK_OR 0xfe00707f

typedef enum {
    INST_TYPE_ALU = 0x100,
    INST_ALU_ADD,
    INST_ALU_ADDI,
    INST_ALU_ADDIW,
    INST_ALU_ADDW,
    INST_ALU_LUI,
    INST_ALU_MUL,
    INST_ALU_MULW,
    INST_ALU_SLTU,
    INST_ALU_SLLIW,
    INST_ALU_SLLI,
    INST_ALU_SLT,
    INST_ALU_SRLI,
    INST_ALU_ANDI,
    INST_ALU_ORI,
    INST_ALU_XORI,
    INST_ALU_OR,

    INST_TYPE_FPU = 0x200,
    INST_FPU_FADD_S,
    INST_FPU_FMADD_S,
    INST_FPU_FMUL_S,
    INST_FPU_FDIV_S,

    INST_TYPE_LS = 0x400,
    INST_LS_LD,
    INST_LS_LW,
    INST_LS_LWU,
    INST_LS_SD,
    INST_LS_SW,    
    INST_LS_FLW,
    INST_LS_FSW,

    INST_TYPE_BRANCH = 0x800,
    INST_BRANCH_BEQ,
    INST_BRANCH_BGEU,
    INST_BRANCH_BLTU,
    INST_BRANCH_BNE,
    INST_BRANCH_AUIPC,
    INST_BRANCH_JAL,
    INST_BRANCH_JALR,

    INST_TYPE_MASK = 0xF00,
    INST_ERROR_CODE = 0xFFF,
    INST_TYPE_NOP = 0x1000,
} INST;
} // endof namespace