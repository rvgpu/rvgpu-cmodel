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

#include "instmask.h"

typedef enum {
    INST_TYPE_ALU = 0x100,
    INST_ALU_ADD,
    INST_ALU_ADDI,
    INST_ALU_ADDIW,
    INST_ALU_ADDW,
    INST_ALU_LUI,
    INST_ALU_MUL,
    INST_ALU_MULW,
    INST_ALU_MULH,
    INST_ALU_SLTU,
    INST_ALU_SLLIW,
    INST_ALU_SLLI,
    INST_ALU_SLT,
    INST_ALU_SLTI,
    INST_ALU_SLTIU,
    INST_ALU_SRLI,
    INST_ALU_SRAI,
    INST_ALU_SUB,
    INST_ALU_SUBW,
    INST_ALU_ANDI,
    INST_ALU_ORI,
    INST_ALU_XORI,
    INST_ALU_OR,

    INST_TYPE_FPU = 0x200,
    INST_FPU_FADD_S,
    INST_FPU_FMADD_S,
    INST_FPU_FMUL_S,
    INST_FPU_FDIV_S,
    INST_FPU_FMSUB_S,
    INST_FPU_FSUB_S,
    INST_FPU_FCVT_S_WU,
    INST_FPU_FCVT_LU_S,
    INST_FPU_FLE_S,
    INST_FPU_FMV_W_X,

    INST_TYPE_LS = 0x400,
    INST_LS_LB,
    INST_LS_LBU,
    INST_LS_LH,
    INST_LS_LHU,
    INST_LS_LW,
    INST_LS_LWU,
    INST_LS_LD,
    INST_LS_SB,
    INST_LS_SH,
    INST_LS_SW,
    INST_LS_SD,
    INST_LS_FLW,
    INST_LS_FSW,

    INST_TYPE_BRANCH = 0x800,
    INST_BRANCH_BEQ,
    INST_BRANCH_BGE,
    INST_BRANCH_BGEU,
    INST_BRANCH_BLTU,
    INST_BRANCH_BNE,
    INST_BRANCH_BLT,
    INST_BRANCH_AUIPC,
    INST_BRANCH_JAL,
    INST_BRANCH_JALR,

    INST_TYPE_MASK = 0xF00,
    INST_ERROR_CODE = 0xFFF,
    INST_TYPE_NOP = 0x1000,
} INST;
} // endof namespace