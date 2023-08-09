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

#include "common/utils.hpp"
#include "common/softfloat.hpp"
#include "fpu.hpp"
#include "encoding.hpp"

using namespace utils;

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
        case encoding::INST_FPU_FSUB_S:
            ret = fsub_s();
            break;
        case encoding::INST_FPU_FCVT_S_WU:
            ret = fcvt_s_wu();
            break;
        case encoding::INST_FPU_FLE_S:
            ret = fle_s();
            break;
        default:
            printf("FPU Inst TODO\n");
            break;
    }

    return ret;
}

uint64_t fpu::fadd_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) + reg2f(inst.frs2);
    printf("[FPU.%d][FADD_S] r[%ld](%f) = %f + %f\n", m_id, inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return f2reg(res);
}

uint64_t fpu::fmul_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) * reg2f(inst.frs2);
    printf("[FPU.%d][FMUL_S] r[%ld](%f) = %f * %f\n", m_id, inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return f2reg(res);
}

uint64_t fpu::fdiv_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) / reg2f(inst.frs2);
    printf("[FPU.%d][FDIV_S] r[%ld](%f) = %f / %f\n", m_id, inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return f2reg(res);
}

uint64_t fpu::fmadd_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) * reg2f(inst.frs2) + reg2f(inst.frs3);
    printf("[FPU.%d][FMADD_S] r[%ld](%f) = %f * %f + %f\n", m_id, inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));
    return f2reg(res);
}

uint64_t fpu::fmsub_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) * reg2f(inst.frs2) - reg2f(inst.frs3);
    printf("[FPU.%d][FMSUB_S] r[%ld](%f) = %f * %f - %f\n", m_id, inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));
    return f2reg(res);
}

uint64_t fpu::fsub_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) - reg2f(inst.frs2);
    printf("[FPU.%d][FSUB_S] r[%ld](%f) = %f + %f\n", m_id, inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return f2reg(res);
}

uint64_t fpu::fcvt_s_wu() {
    float res = ui32_to_f32((uint32_t)inst.rs1);
    printf("[FPU.%d][FCVT_S_WU] r[%lx](%f) = ui32_to_f32(%lx)\n", m_id, inst.rd, res, inst.rs1);
    return f2reg(res);
}

uint64_t fpu::fle_s() {
    uint64_t res;
    res = f32_le(uint32_t(inst.frs1), uint32_t(inst.frs2));
    printf("[FPU.%d][FCVT_S_WU] r[%lx](%ld) = (%f <= %f)\n", m_id, inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return res;
}

