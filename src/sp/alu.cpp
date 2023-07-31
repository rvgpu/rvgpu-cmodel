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

#include "alu.hpp"

alu::alu() {
}

uint64_t alu::run(inst_issue instruction) {
    uint64_t ret = 0;

    inst = instruction;
    switch (inst.code) {
        case encoding::INST_ALU_ADD:
            ret = add();
            break;
        case encoding::INST_ALU_ADDI:
            ret = addi();
            break;
        case encoding::INST_ALU_ADDIW:
            ret = addiw();
            break;
        case encoding::INST_ALU_ADDW:
            ret = addw();
            break;
        case encoding::INST_ALU_MUL:
            ret = mul();
            break;
        case encoding::INST_ALU_MULW:
            ret = mulw();
            break;
        case encoding::INST_ALU_SLTU:
            ret = sltu();
            break;
        case encoding::INST_ALU_SLLIW:
            ret = slliw();
            break;
        case encoding::INST_ALU_SLLI:
            ret = slli();
            break;
        case encoding::INST_ALU_SLT:
            ret = slt();
            break;
        case encoding::INST_ALU_ANDI:
            ret = andi();
            break;
        case encoding::INST_ALU_ORI:
            ret = ori();
            break;
        case encoding::INST_ALU_XORI:
            ret = xori();
            break;
        case encoding::INST_ALU_OR:
            ret = OR();
            break;
    }

    return ret;
}

uint64_t alu::add() {
    int64_t ret = inst.rs1 + inst.rs2;
    printf("[EXEC.ALU.ADD] r[%ld](0x%lx) = 0x%lx + %ld\n", inst.rd, ret, inst.rs1, inst.rs2);
    return ret;
}

uint64_t alu::addi() {
    uint64_t ret  = 0;
    ret = inst.rs1 + inst.i_imm;
    printf("[EXEC.ALU.ADDI] r[%ld](0x%lx) = 0x%lx + %ld\n", inst.rd, ret, inst.rs1, inst.i_imm);

    return ret;
}
uint64_t alu::addiw() {
    int64_t ret = 0;
    int32_t rs1 = inst.rs1;
    int32_t imm = inst.i_imm;
    ret = rs1 + imm;
    printf("[EXEC.ALU.ADDIW] r[%ld](0x%lx) = 0x%x + %d\n", inst.rd, ret, rs1, imm);
    return ret;
}
uint64_t alu::addw() {
    int64_t ret = 0;
    int32_t rs1 = inst.rs1;
    int32_t rs2 = inst.rs2;
    ret = rs1 + rs2;
    printf("[EXEC.ALU.ADDW] r[%ld](0x%lx) = 0x%x + %d\n", inst.rd, ret, rs1, rs2);
    return ret;
}

uint64_t alu::mul() {
    int64_t ret = 0;
    ret = int64_t(inst.rs1 * inst.rs2);
    printf("[EXEC.ALU.MUL] r[%ld](0x%lx) = 0x%lx * %ld\n", inst.rd, ret, inst.rs1, inst.rs2);
    return ret;
}

uint64_t alu::mulw() {
    int64_t ret = 0;
    int32_t rs1 = inst.rs1;
    int32_t rs2 = inst.rs2;
    ret = int64_t(rs1 * rs2);
    printf("[EXEC.ALU.MULW] r[%ld](0x%lx) = 0x%x * %d\n", inst.rd, ret, rs1, rs2);
    return ret;
}
uint64_t alu::sltu() {
    uint64_t ret = 0;
    printf("[EXEC.ALU.SLTU]\n");
    return ret;
}
uint64_t alu::slliw() {
    uint64_t ret = 0;
    ret = int32_t(inst.rs1 << (inst.i_imm & 0x3F));
    printf("[EXEC.ALU.SLLIW] r[%ld](0x%lx) = 0x%lx << %ld\n", inst.rd, ret, inst.rs1, (inst.i_imm & 0x3F));
    return ret;
}
uint64_t alu::slli() {
    int64_t ret = 0;
    ret = (inst.rs1 << (inst.i_imm & 0x3F));
    printf("[EXEC.ALU.SLLI] r[%ld](0x%lx) = 0x%lx << %ld\n", inst.rd, ret, inst.rs1, (inst.i_imm & 0x3F));
    return ret;
}
uint64_t alu::slt() {
    int64_t ret = 0;
    ret = int64_t(inst.rs1) < int64_t(inst.rs2);
    printf("[EXEC.ALU.SLT] r[%ld](0x%lx) = 0x%lx < %ld\n", inst.rd, ret, int64_t(inst.rs1), int64_t(inst.rs2));
    return ret;
}
uint64_t alu::andi() {
    uint64_t ret = 0;
    ret = inst.i_imm & inst.rs1;
    printf("[EXEC.ALU.ANDI] r[%ld](0x%lx) = 0x%lx & %ld\n", inst.rd, ret, inst.i_imm, inst.rs1);
    return ret;
}
uint64_t alu::ori() {
    uint64_t ret = 0;
    ret = inst.i_imm | inst.rs1;
    printf("[EXEC.ALU.ORI] r[%ld](0x%lx) = 0x%lx | %ld\n", inst.rd, ret, inst.i_imm, inst.rs1);
    return ret;
}
uint64_t alu::xori() {
    uint64_t ret = 0;
    ret = inst.i_imm ^ inst.rs1;
    printf("[EXEC.ALU.XORI] r[%ld](0x%lx) = 0x%lx ^ %ld\n", inst.rd, ret, inst.i_imm, inst.rs1);
    return ret;
}
uint64_t alu::OR() {
    uint64_t ret = 0;
    ret = inst.rs1 | inst.rs2;
    printf("[EXEC.ALU.OR] r[%ld](0x%lx) = 0x%lx | %ld\n", inst.rd, ret, inst.rs1, inst.rs2);
    return ret;
}
