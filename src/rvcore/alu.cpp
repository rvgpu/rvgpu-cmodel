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
#include "mext.hpp"

alu::alu(uint32_t id) {
    m_id = id;
    xlen = 64;
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
        case encoding::INST_ALU_AND:
            ret = AND();
            break;
        case encoding::INST_ALU_ANDI:
            ret = andi();
            break;
        case encoding::INST_ALU_DIV:
            ret = div();
            break;
        case encoding::INST_ALU_DIVU:
            ret = divu();
            break;
        case encoding::INST_ALU_DIVUW:
            ret = divuw();
            break;
        case encoding::INST_ALU_DIVW:
            ret = divw();
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
        case encoding::INST_ALU_MULHSU:
            ret = mulhsu();
            break;
        case encoding::INST_ALU_MULHU:
            ret = mulhu();
            break;
        case encoding::INST_ALU_SLTU:
            ret = sltu();
            break;
        case encoding::INST_ALU_SLLIW:
            ret = slliw();
            break;
        case encoding::INST_ALU_SLL:
            ret = sll();
            break;
        case encoding::INST_ALU_SLLI:
            ret = slli();
            break;
        case encoding::INST_ALU_SLLW:
            ret = sllw();
            break;
        case encoding::INST_ALU_SLT:
            ret = slt();
            break;
        case encoding::INST_ALU_SLTI:
            ret = slti();
            break;
        case encoding::INST_ALU_SLTIU:
            ret = sltiu();
            break;
        case encoding::INST_ALU_SRL:
            ret = srl();
            break;
        case encoding::INST_ALU_SRLI:
            ret = srli();
            break;
        case encoding::INST_ALU_SRLIW:
            ret = srliw();
            break;
        case encoding::INST_ALU_SRLW:
            ret = srlw();
            break;
        case encoding::INST_ALU_SRA:
            ret = sra();
            break;
        case encoding::INST_ALU_SRAI:
            ret = srai();
            break;
        case encoding::INST_ALU_SRAIW:
            ret = sraiw();
            break;
        case encoding::INST_ALU_SRAW:
            ret = sraw();
            break;
        case encoding::INST_ALU_SUB:
            ret = sub();
            break;
        case encoding::INST_ALU_SUBW:
            ret = subw();
            break;
        case encoding::INST_ALU_REM:
            ret = rem();
            break;
        case encoding::INST_ALU_REMU:
            ret = remu();
            break;
        case encoding::INST_ALU_REMW:
            ret = remw();
            break;
        case encoding::INST_ALU_REMUW:
            ret = remuw();
            break;
        case encoding::INST_ALU_ORI:
            ret = ori();
            break;
        case encoding::INST_ALU_XORI:
            ret = xori();
            break;
        case encoding::INST_ALU_XOR:
            ret = XOR();
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

writeback_t alu::div() {
    uint64_t res = proc_div(inst.rs1, inst.rs2);
    ALU_INFO("[DIV] r[%ld](0x%lx) = 0x%x / %d\n", inst.rd, res, rs1, rs2);
    return writeback_t {inst.rd, res};
}

writeback_t alu::divu() {
    uint64_t res = proc_divu(inst.rs1, inst.rs2);
    ALU_INFO("[DIVU] r[%ld](0x%lx) = 0x%x / %d\n", inst.rd, res, rs1, rs2);
    return writeback_t {inst.rd, res};
}

writeback_t alu::divw() {
    uint64_t res = proc_divw(inst.rs1, inst.rs2);
    ALU_INFO("[DIVW] r[%ld](0x%lx) = 0x%x / %d\n", inst.rd, res, rs1, rs2);
    return writeback_t {inst.rd, res};
}

writeback_t alu::divuw() {
    uint64_t res = proc_divuw(inst.rs1, inst.rs2);
    ALU_INFO("[DIVUW] r[%ld](0x%lx) = 0x%x / %d\n", inst.rd, res, rs1, rs2);
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
    uint64_t res = proc_mulh(inst.rs1, inst.rs2);
    ALU_INFO("[MULH] r[%ld](0x%lx) = 0x%ld * %ld\n", inst.rd, ret, inst.rs1, inst.rs2);
    return writeback_t {inst.rd, res};
}

writeback_t alu::mulhsu() {
    uint64_t res = proc_mulhsu(inst.rs1, inst.rs2);
    ALU_INFO("[MULHSU] r[%ld](0x%lx) = 0x%ld * %ld\n", inst.rd, ret, inst.rs1, inst.rs2);
    return writeback_t {inst.rd, res};
}

writeback_t alu::mulhu() {
    uint64_t res = proc_mulhu(inst.rs1, inst.rs2);
    ALU_INFO("[MULHSU] r[%ld](0x%lx) = 0x%ld * %ld\n", inst.rd, ret, inst.rs1, inst.rs2);
    return writeback_t {inst.rd, res};
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

writeback_t alu::sltiu() {
    uint64_t res = (inst.rs1 < reg_t(inst.i_imm));
    ALU_INFO("[SLTIU] r[%ld](0x%lx) = (0x%lx < 0x%lx) ? 1 : 0\n", inst.rd, res, (inst.rs1), reg_t(inst.i_imm));
    return writeback_t {inst.rd, res};
}

writeback_t alu::slliw() {
    uint64_t res = sext32(inst.rs1 << SHAMT)
    ALU_INFO("[SLLIW] r[%ld](0x%lx) = 0x%lx << %ld\n", inst.rd, res, inst.rs1, (inst.i_imm & 0x3F));
    return writeback_t {inst.rd, res};
}

writeback_t alu::sllw() {
    uint64_t res = (sext32(inst.rs1 << (inst.rs2 & 0x1F)));
    ALU_INFO("[SLLW] r[%ld](0x%lx) = 0x%lx << %ld\n", inst.rd, res, inst.rs1, (inst.rs2 & 0x1F));
    return writeback_t {inst.rd, res};
}

writeback_t alu::sll() {
    uint64_t res = (sext_xlen(inst.rs1 << (inst.rs2 & (xlen-1))));
    ALU_INFO("[SLL] r[%ld](0x%lx) = 0x%lx << %ld\n", inst.rd, res, inst.rs1, (inst.rs2 & (xlen-1)));
    return writeback_t {inst.rd, res};
}

writeback_t alu::slli() {
    uint64_t res = sext_xlen(inst.rs1 << SHAMT);
    ALU_INFO("[SLLI] r[%ld](0x%lx) = 0x%lx << %ld\n", inst.rd, res, inst.rs1, SHAMT);
    return writeback_t {inst.rd, res};
}

writeback_t alu::srl() {
    uint64_t res = (sext_xlen(zext_xlen(inst.rs1) >> (inst.rs2 & (xlen-1))));
    ALU_INFO("[SRL] r[%ld](0x%lx) = 0x%lx >> %ld\n", inst.rd, res, inst.rs1, (inst.rs2 & (xlen-1)));
    return writeback_t {inst.rd, uint64_t(res)};
}

writeback_t alu::srli() {
    uint64_t res = sext_xlen(zext_xlen(inst.rs1) >> SHAMT);
    ALU_INFO("[SRLI] r[%ld](0x%lx) = 0x%lx >> %ld\n", inst.rd, res, inst.rs1, SHAMT);
    return writeback_t {inst.rd, uint64_t(res)};
}

writeback_t alu::srliw() {
    uint64_t res = (sext32((uint32_t)inst.rs1 >> SHAMT));
    ALU_INFO("[SRLIW] r[%ld](0x%lx) = 0x%lx >> %ld\n", inst.rd, res, inst.rs1, SHAMT);
    return writeback_t {inst.rd, uint64_t(res)};
}

writeback_t alu::srlw() {
    uint64_t res = (sext32((uint32_t)inst.rs1 >> (inst.rs2 & 0x1F)));
    ALU_INFO("[SRLW] r[%ld](0x%lx) = 0x%lx >> %ld\n", inst.rd, res, inst.rs1, (inst.rs2 & 0x1F));
    return writeback_t {inst.rd, uint64_t(res)};
}

writeback_t alu::sra() {
    uint64_t res = (sext_xlen(sext_xlen(inst.rs1) >> (inst.rs2 & (xlen - 1))));
    ALU_INFO("[SRA] r[%ld](0x%lx) = 0x%lx >> %ld\n", inst.rd, res, inst.rs1, (inst.rs2 & (xlen-1)));
    return writeback_t {inst.rd, res};
}

writeback_t alu::srai() {
    uint64_t res = sext_xlen(sext_xlen(inst.rs1) >> SHAMT)
    ALU_INFO("[SRAI] r[%ld](0x%lx) = 0x%lx >> %ld\n", inst.rd, res, inst.rs1, SHAMT);
    return writeback_t {inst.rd, res};
}

writeback_t alu::sraiw() {
    uint64_t res = (sext32(int32_t(inst.rs1) >> SHAMT));
    ALU_INFO("[SRAIW] r[%ld](0x%lx) = 0x%lx >> %ld\n", inst.rd, res, inst.rs1, SHAMT);
    return writeback_t {inst.rd, res};
}

writeback_t alu::sraw() {
    uint64_t res = (sext32(int32_t(inst.rs1) >> (inst.rs2 & 0x1F)));
    ALU_INFO("[SRAIW] r[%ld](0x%lx) = 0x%lx >> %ld\n", inst.rd, res, inst.rs1, (inst.rs2 & 0x1F));
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

writeback_t alu::rem() {
    uint64_t res = proc_rem(inst.rs1, inst.rs2);
    ALU_INFO("[REM] r[%ld](0x%lx) = 0x%lx % %ld\n", inst.rd, res, int64_t(inst.rs1), int64_t(inst.rs2));
    return writeback_t {inst.rd, res};
}

writeback_t alu::remu() {
    uint64_t res = proc_remu(inst.rs1, inst.rs2);
    ALU_INFO("[REMU] r[%ld](0x%lx) = 0x%lx % %ld\n", inst.rd, res, int64_t(inst.rs1), int64_t(inst.rs2));
    return writeback_t {inst.rd, res};
}

writeback_t alu::remw() {
    uint64_t res = proc_remw(inst.rs1, inst.rs2);
    ALU_INFO("[REMW] r[%ld](0x%lx) = 0x%lx % %ld\n", inst.rd, res, int64_t(inst.rs1), int64_t(inst.rs2));
    return writeback_t {inst.rd, res};
}

writeback_t alu::remuw() {
    uint64_t res = proc_remuw(inst.rs1, inst.rs2);
    ALU_INFO("[REMUW] r[%ld](0x%lx) = 0x%lx % %ld\n", inst.rd, res, int64_t(inst.rs1), int64_t(inst.rs2));
    return writeback_t {inst.rd, res};
}

writeback_t alu::andi() {
    uint64_t res = (inst.i_imm & inst.rs1);
    ALU_INFO("[ANDI] r[%ld](0x%lx) = 0x%lx & %ld\n", inst.rd, res, inst.i_imm, inst.rs1);
    return writeback_t {inst.rd, res};
}

writeback_t alu::AND() {
    uint64_t res = (inst.rs1 & inst.rs2);
    ALU_INFO("[AND] r[%ld](0x%lx) = 0x%lx & %ld\n", inst.rd, res, inst.rs1, inst.rs1);
    return writeback_t {inst.rd, res};
}

writeback_t alu::ori() {
    uint64_t res = (inst.i_imm | inst.rs1);
    ALU_INFO("[ORI] r[%ld](0x%lx) = 0x%lx | %ld\n", inst.rd, res, inst.i_imm, inst.rs1);
    return writeback_t {inst.rd, res};
}

writeback_t alu::XOR() {
    uint64_t res = (inst.rs1 ^ inst.rs2);
    ALU_INFO("[XORI] r[%ld](0x%lx) = 0x%lx ^ %ld\n", inst.rd, res, inst.rs1, inst.rs1);
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
