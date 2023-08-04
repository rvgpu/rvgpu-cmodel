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
#include <bit>

#include "fpu.hpp"
#include "encoding.hpp"

fpu::fpu(uint32_t id) {
    m_id = id;
}

uint64_t fpu::run(inst_issue instruction) {
    uint64_t ret = 0;

    inst = instruction;
    switch (inst.code) {
        case encoding::INST_FPU_FADD_S:
            ret = fadd_s();
            break;
        case encoding::INST_FPU_FMUL_S:
            ret = fmul_s();
            break;
        case encoding::INST_FPU_FDIV_S:
            ret = fdiv_s();
            break;
        case encoding::INST_FPU_FMADD_S:
            ret = fmadd_s();
            break;
        case encoding::INST_FPU_FMSUB_S:
            ret = fmsub_s();
            break;
        default:
            printf("FPU Inst TODO\n");
            break;
    }

    return ret;
}

float fpu::reg2f(uint64_t data) {
    uint32_t data32 = data;
    return std::bit_cast<float>(data32);
}

uint64_t fpu::f2reg(float data) {
    return uint64_t(std::bit_cast<uint32_t>(data));
}

uint64_t fpu::fadd_s() {
    float res = 0.0f;
    res = reg2f(inst.rs1) + reg2f(inst.rs2);
    printf("[FPU.%d][FADD_S] r[%ld](%f) = %f + %f\n", m_id, inst.rd, res, reg2f(inst.rs1), reg2f(inst.rs2));
    return f2reg(res);
}

uint64_t fpu::fmul_s() {
    float res = 0.0f;
    res = reg2f(inst.rs1) * reg2f(inst.rs2);
    printf("[FPU.%d][FMUL_S] r[%ld](%f) = %f * %f\n", m_id, inst.rd, res, reg2f(inst.rs1), reg2f(inst.rs2));
    return f2reg(res);
}

uint64_t fpu::fdiv_s() {
    float res = 0.0f;
    res = reg2f(inst.rs1) / reg2f(inst.rs2);
    printf("[FPU.%d][FDIV_S] r[%ld](%f) = %f / %f\n", m_id, inst.rd, res, reg2f(inst.rs1), reg2f(inst.rs2));
    return f2reg(res);
}

uint64_t fpu::fmadd_s() {
    float res = 0.0f;
    res = reg2f(inst.rs1) * reg2f(inst.rs2) + reg2f(inst.rs3);
    printf("[FPU.%d][FMADD_S] r[%ld](%f) = %f * %f + %f\n", m_id, inst.rd, res, reg2f(inst.rs1), reg2f(inst.rs2), reg2f(inst.rs3));
    return f2reg(res);
}

uint64_t fpu::fmsub_s() {
    float res = 0.0f;
    res = reg2f(inst.rs1) * reg2f(inst.rs2) - reg2f(inst.rs3);
    printf("[FPU.%d][FMSUB_S] r[%ld](%f) = %f * %f - %f\n", m_id, inst.rd, res, reg2f(inst.rs1), reg2f(inst.rs2), reg2f(inst.rs3));
    return f2reg(res);
}