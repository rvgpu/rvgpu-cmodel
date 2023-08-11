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

uint64_t alu::util_mulhu(uint64_t a, uint64_t b)
{
    uint64_t t;
    uint32_t y1, y2, y3;
    uint64_t a0 = (uint32_t)a, a1 = a >> 32;
    uint64_t b0 = (uint32_t)b, b1 = b >> 32;

    t = a1*b0 + ((a0*b0) >> 32);
    y1 = t;
    y2 = t >> 32;

    t = a0*b1 + y1;

    t = a1*b1 + y2 + (t >> 32);
    y2 = t;
    y3 = t >> 32;

    return ((uint64_t)y3 << 32) | y2;
}

alu::alu(uint32_t id) {
    m_id = id;
}

writeback_t alu::run(inst_issue instruction) {
    writeback_t ret = {};

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
        case encoding::INST_ALU_LUI:
            ret = lui();
            break;
        case encoding::INST_ALU_MUL:
            ret = mul();
            break;
        case encoding::INST_ALU_MULW:
            ret = mulw();
            break;
        case encoding::INST_ALU_MULH:
            ret = mulh();
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
        case encoding::INST_ALU_SLTI:
            ret = slti();
            break;
        case encoding::INST_ALU_SRLI:
            ret = srli();
            break;
        case encoding::INST_ALU_SRAI:
            ret = srai();
            break;
        case encoding::INST_ALU_SUB:
            ret = sub();
            break;
        case encoding::INST_ALU_SUBW:
            ret = subw();
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
        default:
            printf("ALU.%d Inst TODO\n", m_id);
            break;
    }

    return ret;
}

writeback_t alu::add() {
    uint64_t res = sext_xlen(inst.rs1 + inst.rs2);
    ALU_INFO("[ADD] r[%ld](0x%lx) = 0x%lx + %ld\n", inst.rd, res, inst.rs1, inst.rs2);
    return writeback_t {inst.rd, res};
}

writeback_t alu::addi() {
    uint64_t res = sext_xlen(inst.rs1 + inst.i_imm);
    ALU_INFO("[ADDI] r[%ld](0x%lx) = 0x%lx + %ld\n", inst.rd, res, inst.rs1, inst.i_imm);
    return writeback_t {inst.rd, res};
}

writeback_t alu::addiw() {
    uint64_t res = sext32(inst.i_imm + inst.rs1);
    ALU_INFO("[ADDIW] r[%ld](0x%lx) = 0x%x + %d\n", inst.rd, res, rs1, imm);
    return writeback_t {inst.rd, res};
}
writeback_t alu::addw() {
    uint64_t res = sext32(inst.rs1 + inst.rs2);
    ALU_INFO("[ADDW] r[%ld](0x%lx) = 0x%x + %d\n", inst.rd, res, rs1, rs2);
    return writeback_t {inst.rd, res};
}

writeback_t alu::lui() {
    uint64_t res = inst.u_imm;
    ALU_INFO("[LUI] r[%ld](0x%lx) = 0x%lx\n", inst.rd, res, inst.u_imm);
    return writeback_t {inst.rd, res};
}

writeback_t alu::mul() {
    uint64_t res = sext_xlen(inst.rs1 * inst.rs2);
    ALU_INFO("[MUL] r[%ld](0x%lx) = 0x%lx * %ld\n", inst.rd, res, inst.rs1, inst.rs2);
    return writeback_t {inst.rd, res};
}

writeback_t alu::mulw() {
    uint64_t res = sext32(inst.rs1 * inst.rs2);
    ALU_INFO("[MULW] r[%ld](0x%lx) = 0x%x * %d\n", inst.rd, res, rs1, rs2);
    return writeback_t {inst.rd, res};
}

writeback_t alu::mulh() {
    int64_t ret = 0;
    int64_t a = inst.rs1;
    int64_t b = inst.rs2;

    int negate = (a < 0) != (b < 0);
    uint64_t res = util_mulhu(a < 0 ? -a : a, b < 0 ? -b : b);
    ret =  negate ? ~res + (a * b == 0) : res;
    ALU_INFO("[MULH] r[%ld](0x%lx) = 0x%ld * %ld\n", inst.rd, ret, inst.rs1, inst.rs2);
    return writeback_t {inst.rd, uint64_t(ret)};
}

writeback_t alu::sltu() {
    uint64_t res = (inst.rs1 < inst.rs2);
    ALU_INFO("[SLTU] r[%ld](0x%lx) = (0x%lx < 0x%lx) ? 1 : 0\n", inst.rd, res, rs1, rs2);
    return writeback_t {inst.rd, res};
}

writeback_t alu::slti() {
    uint64_t res = (sreg_t(inst.rs1) < sreg_t(inst.i_imm));
    ALU_INFO("[SLTI] r[%ld](0x%lx) = (0x%lx < 0x%lx) ? 1 : 0\n", inst.rd, res, sreg_t(inst.rs1), sreg_t(inst.i_imm));
    return writeback_t {inst.rd, res};
}

writeback_t alu::slliw() {
    uint64_t res = sext32(inst.rs1 << SHAMT)
    ALU_INFO("[SLLIW] r[%ld](0x%lx) = 0x%lx << %ld\n", inst.rd, res, inst.rs1, (inst.i_imm & 0x3F));
    return writeback_t {inst.rd, res};
}

writeback_t alu::slli() {
    uint64_t res = sext_xlen(inst.rs1 << SHAMT);
    ALU_INFO("[SLLI] r[%ld](0x%lx) = 0x%lx << %ld\n", inst.rd, res, inst.rs1, (inst.i_imm & 0x3F));
    return writeback_t {inst.rd, res};
}

writeback_t alu::srli() {
    uint64_t res = sext_xlen(zext_xlen(inst.rs1) >> SHAMT);
    ALU_INFO("[SRLI] r[%ld](0x%lx) = 0x%lx >> %ld\n", inst.rd, res, inst.rs1, (inst.i_imm & 0x3F));
    return writeback_t {inst.rd, uint64_t(res)};
}

writeback_t alu::srai() {
    uint64_t res = sext_xlen(sext_xlen(inst.rs1) >> SHAMT)
    ALU_INFO("[SRLI] r[%ld](0x%lx) = 0x%lx >> %ld\n", inst.rd, res, inst.rs1, (inst.i_imm & 0x3F));
    return writeback_t {inst.rd, res};
}

writeback_t alu::slt() {
    uint64_t res = (sreg_t(inst.rs1) < sreg_t(inst.rs2));
    ALU_INFO("[SLT] r[%ld](0x%lx) = 0x%lx < %ld\n", inst.rd, res, int64_t(inst.rs1), int64_t(inst.rs2));
    return writeback_t {inst.rd, res};
}

writeback_t alu::sub() {
    uint64_t res = (sext_xlen(inst.rs1 - inst.rs2));
    ALU_INFO("[SUB] r[%ld](0x%lx) = 0x%lx - %ld\n", inst.rd, res, int64_t(inst.rs1), int64_t(inst.rs2));
    return writeback_t {inst.rd, res};
}

writeback_t alu::subw() {
    uint64_t res = (sext32(inst.rs1 - inst.rs2));
    ALU_INFO("[SUBW] r[%ld](0x%lx) = 0x%lx - %ld\n", inst.rd, res, int64_t(inst.rs1), int64_t(inst.rs2));
    return writeback_t {inst.rd, res};
}

writeback_t alu::andi() {
    uint64_t res = (inst.i_imm & inst.rs1);
    ALU_INFO("[ANDI] r[%ld](0x%lx) = 0x%lx & %ld\n", inst.rd, res, inst.i_imm, inst.rs1);
    return writeback_t {inst.rd, res};
}

writeback_t alu::ori() {
    uint64_t res = (inst.i_imm | inst.rs1);
    ALU_INFO("[ORI] r[%ld](0x%lx) = 0x%lx | %ld\n", inst.rd, res, inst.i_imm, inst.rs1);
    return writeback_t {inst.rd, res};
}

writeback_t alu::xori() {
    uint64_t res = (inst.i_imm ^ inst.rs1);
    ALU_INFO("[XORI] r[%ld](0x%lx) = 0x%lx ^ %ld\n", inst.rd, res, inst.i_imm, inst.rs1);
    return writeback_t {inst.rd, res};
}

writeback_t alu::OR() {
    uint64_t res = (inst.rs1 | inst.rs2);
    ALU_INFO("[OR] r[%ld](0x%lx) = 0x%lx | %ld\n", inst.rd, res, inst.rs1, inst.rs2);
    return writeback_t {inst.rd, res};
}
