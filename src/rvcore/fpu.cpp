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

#include "common/debug.hpp"
#include "common/utils.hpp"
#include "softfloat/softfloat.h"
#include "fpu.hpp"
#include "encoding.hpp"

using namespace utils;

fpu::fpu(uint32_t id) {
    m_id = id;
}

writeback_t fpu::run(inst_issue instruction) {
    writeback_t ret = {};

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
        case encoding::INST_FPU_FCVT_LU_S:
            ret = fcvt_lu_s();
            break;
        case encoding::INST_FPU_FLE_S:
            ret = fle_s();
            break;
        case encoding::INST_FPU_FMV_W_X:
            ret = fmv_w_x();
            break;
        default:
            printf("FPU Inst TODO\n");
            break;
    }

    return ret;
}

writeback_t fpu::fadd_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) + reg2f(inst.frs2);
    FPU_INFO("[FADD_S] r[%ld](%f) = %f + %f\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return writeback_t {inst.rd, f2reg(res)};
}

writeback_t fpu::fmul_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) * reg2f(inst.frs2);
    FPU_INFO("[FMUL_S] r[%ld](%f) = %f * %f\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return writeback_t {inst.rd, f2reg(res)};
}

writeback_t fpu::fdiv_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) / reg2f(inst.frs2);
    FPU_INFO("[FDIV_S] r[%ld](%f) = %f / %f\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return writeback_t {inst.rd, f2reg(res)};
}

writeback_t fpu::fmadd_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) * reg2f(inst.frs2) + reg2f(inst.frs3);
    FPU_INFO("[FMADD_S] r[%ld](%f) = %f * %f + %f\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));
    return writeback_t {inst.rd, f2reg(res)};
}

writeback_t fpu::fmsub_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) * reg2f(inst.frs2) - reg2f(inst.frs3);
    FPU_INFO("[FMSUB_S] r[%ld](%f) = %f * %f - %f\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));
    return writeback_t {inst.rd, f2reg(res)};
}

writeback_t fpu::fsub_s() {
    float res = 0.0f;
    res = reg2f(inst.frs1) - reg2f(inst.frs2);
    FPU_INFO("[FSUB_S] r[%ld](%f) = %f + %f\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return writeback_t {inst.rd, f2reg(res)};
}

writeback_t fpu::fcvt_s_wu() {
    float32_t res = ui32_to_f32((uint32_t)inst.rs1);
    FPU_INFO("[FCVT_S_WU] r[%lx](%f) = ui32_to_f32(%lx)\n", inst.rd, res, inst.rs1);
    return writeback_t {inst.rd, uint64_t(res.v)};
}

writeback_t fpu::fcvt_lu_s() {
    uint64_t res = f32_to_ui64(float32_t(inst.frs1), getrm(), true);
    FPU_INFO("[FCVT_LU_S] r[%lx](%lx) = f32_to_ui64(%f)\n", inst.rd, res, reg2f(inst.frs1));
    return writeback_t {inst.rd, res};
}

writeback_t fpu::fle_s() {
    uint64_t res;
    res = f32_le(float32_t(inst.frs1), float32_t(inst.frs2));
    FPU_INFO("[FLE_S] r[%lx](%ld) = (%f <= %f)\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return writeback_t {inst.rd, res};
}

writeback_t fpu::fmv_w_x() {
    float res = reg2f(inst.rs1);
    FPU_INFO("[FMV_W_X] r[%lx](%f) = %f\n", inst.rd, res, reg2f(inst.rs1));
    return writeback_t {inst.rd, f2reg(res)};
}

int32_t fpu::getrm()
{
    int rm = inst.rm;
    if (rm == 7) {
        printf("TODO FSCRs\n");
        // rm = STATE.frm->read();
    }
    if (rm > 4) {
        RVGPU_ERROR_PRINT("illegal instruction: %x\n", inst.bits);
    }

    return rm;
}