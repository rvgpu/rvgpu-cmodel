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
        case encoding::INST_FPU_FADD_D:
            ret = fadd_d();
            break;
        case encoding::INST_FPU_FSUB_S:
            ret = fsub_s();
            break;
        case encoding::INST_FPU_FSUB_D:
            ret = fsub_d();
            break;
        case encoding::INST_FPU_FMUL_S:
            ret = fmul_s();
            break;
        case encoding::INST_FPU_FMUL_D:
            ret = fmul_d();
            break;
        case encoding::INST_FPU_FDIV_S:
            ret = fdiv_s();
            break;
        case encoding::INST_FPU_FDIV_D:
            ret = fdiv_d();
            break;
        case encoding::INST_FPU_FMADD_S:
            ret = fmadd_s();
            break;
        case encoding::INST_FPU_FMADD_D:
            ret = fmadd_d();
            break;
        case encoding::INST_FPU_FMSUB_S:
            ret = fmsub_s();
            break;
        case encoding::INST_FPU_FMSUB_D:
            ret = fmsub_d();
            break;
        case encoding::INST_FPU_FNMADD_S:
            ret = fnmadd_s();
            break;
        case encoding::INST_FPU_FNMADD_D:
            ret = fnmadd_d();
            break;
        case encoding::INST_FPU_FNMSUB_S:
            ret = fnmsub_s();
            break;
        case encoding::INST_FPU_FNMSUB_D:
            ret = fnmsub_d();
            break;
        case encoding::INST_FPU_FMAX_S:
            ret = fmax_s();
            break;
        case encoding::INST_FPU_FMAX_D:
            ret = fmax_d();
            break;
        case encoding::INST_FPU_FMIN_S:
            ret = fmin_s();
            break;
        case encoding::INST_FPU_FMIN_D:
            ret = fmin_d();
            break;
        case encoding::INST_FPU_FSQRT_S:
            ret = fsqrt_s();
            break;
        case encoding::INST_FPU_FSQRT_D:
            ret = fsqrt_d();
            break;
        case encoding::INST_FPU_FCVT_S_WU:
            ret = fcvt_s_wu();
            break;
        case encoding::INST_FPU_FCVT_LU_S:
            ret = fcvt_lu_s();
            break;
        case encoding::INST_FPU_FEQ_S:
            ret = feq_s();
            break;
        case encoding::INST_FPU_FEQ_D:
            ret = feq_d();
            break;
        case encoding::INST_FPU_FLE_S:
            ret = fle_s();
            break;
        case encoding::INST_FPU_FLE_D:
            ret = fle_d();
            break;
        case encoding::INST_FPU_FLT_S:
            ret = flt_s();
            break;
        case encoding::INST_FPU_FLT_D:
            ret = flt_d();
            break;
        case encoding::INST_FPU_FSGNJ_S:
            ret = fsgnj_s();
            break;
        case encoding::INST_FPU_FSGNJ_D:
            ret = fsgnj_d();
            break;
        case encoding::INST_FPU_FSGNJN_S:
            ret = fsgnjn_s();
            break;
        case encoding::INST_FPU_FSGNJN_D:
            ret = fsgnjn_d();
            break;
        case encoding::INST_FPU_FSGNJX_S:
            ret = fsgnjx_s();
            break;
        case encoding::INST_FPU_FSGNJX_D:
            ret = fsgnjx_d();
            break;
        case encoding::INST_FPU_FMV_W_X:
            ret = fmv_w_x();
            break;
        case encoding::INST_FPU_FMV_X_W:
            ret = fmv_x_w();
            break;
        case encoding::INST_FPU_FMV_D_X:
            ret = fmv_d_x();
            break;
        case encoding::INST_FPU_FMV_X_D:
            ret = fmv_x_d();
            break;
        default:
            printf("FPU Inst TODO\n");
            break;
    }

    return ret;
}

writeback_t fpu::fadd_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t res = f32_add(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FADD_S] r[%ld](%f) = %f + %f\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fadd_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t res = f64_add(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FADD_D] r[%ld](%f) = %f + %f\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fsub_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t res = f32_sub(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FSUB_S] r[%ld](%f) = %f - %f\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fsub_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t res = f64_sub(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FSUB_D] r[%ld](%f) = %f - %f\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fmul_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t res = f32_mul(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FMUL_S] r[%ld](%f) = %f * %f\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fmul_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t res = f64_mul(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FMUL_D] r[%ld](%f) = %f * %f\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fdiv_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t res = f32_div(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FDIV_S] r[%ld](%f) = %f / %f\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fdiv_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t res = f64_div(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FDIV_D] r[%ld](%f) = %f / %f\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fmadd_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t frs3 = { (uint32_t)inst.frs3 };
    float32_t res = f32_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FMADD_S] r[%ld](%f) = %f * %f + %f\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fmadd_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t frs3 = { (uint64_t)inst.frs3 };
    float64_t res = f64_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FMADD_D] r[%ld](%f) = %f * %f + %f\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2), reg2d(inst.frs3));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fmsub_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t frs3 = { (uint32_t)inst.frs3 ^ F32_SIGN };
    float32_t res = f32_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FMSUB_S] r[%ld](%f) = %f * %f - %f\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fmsub_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t frs3 = { (uint64_t)inst.frs3 ^ F64_SIGN };
    float64_t res = f64_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FMSUB_D] r[%ld](%f) = %f * %f - %f\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2), reg2d(inst.frs3));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fnmadd_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 ^ F32_SIGN };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t frs3 = { (uint32_t)inst.frs3 ^ F32_SIGN };
    float32_t res = f32_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FNMADD_S] r[%ld](%f) = -(%f * %f + %f)\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fnmadd_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 ^ F64_SIGN };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t frs3 = { (uint64_t)inst.frs3 ^ F64_SIGN };
    float64_t res = f64_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FNMADD_D] r[%ld](%f) = -(%f * %f + %f)\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2), reg2d(inst.frs3));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fnmsub_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 ^ F32_SIGN };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t frs3 = { (uint32_t)inst.frs3 };
    float32_t res = f32_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FNMSUB_S] r[%ld](%f) = -(%f * %f - %f)\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fnmsub_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 ^ F64_SIGN };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t frs3 = { (uint64_t)inst.frs3 };
    float64_t res = f64_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FNMSUB_D] r[%ld](%f) = -(%f * %f - %f)\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2), reg2d(inst.frs3));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fmax_s() {
    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t res = f32_max(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FMAX_S] r[%ld](%f) = max(%f, %f)\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fmax_d() {
    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t res = f64_max(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FMAX_D] r[%ld](%f) = max(%f, %f)\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fmin_s() {
    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t res = f32_min(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FMIN_S] r[%ld](%f) = min(%f, %f)\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fmin_d() {
    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t res = f64_min(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FMIN_D] r[%ld](%f) = min(%f, %f)\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fsqrt_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t res = f32_sqrt(frs1);

    set_fp_exceptions();

    FPU_INFO("[FSQRT_S] r[%ld](%f) = sqrt(%f)\n", inst.rd, reg2f(res.v), reg2f(inst.frs1));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fsqrt_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t res = f64_sqrt(frs1);

    set_fp_exceptions();

    FPU_INFO("[FSQRT_D] r[%ld](%f) = sqrt(%f)\n", inst.rd, reg2d(res.v), reg2d(inst.frs1));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fcvt_s_wu() {
    float32_t res = ui32_to_f32((uint32_t)inst.rs1);
    FPU_INFO("[FCVT_S_WU] r[%lx](%f) = ui32_to_f32(%lx)\n", inst.rd, reg2f(res.v), inst.rs1);
    return writeback_t {inst.frd, uint64_t(res.v)};
}

writeback_t fpu::fcvt_lu_s() {
    uint64_t res = f32_to_ui64(float32_t(inst.frs1), get_rounding_mode(), true);
    FPU_INFO("[FCVT_LU_S] r[%lx](%lx) = f32_to_ui64(%f)\n", inst.rd, res, reg2f(inst.frs1));
    return writeback_t {inst.rd, res};
}

writeback_t fpu::feq_s() {
    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    uint64_t res = f32_eq(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FEQ_S] r[%ld](%ld) = (%f == %f)\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.rd, res};
}

writeback_t fpu::feq_d() {
    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    uint64_t res = f64_eq(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FEQ_D] r[%ld](%ld) = (%f == %f)\n", inst.rd, res, reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.rd, res};
}

writeback_t fpu::fle_s() {
    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    uint64_t res = f32_le(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FLE_S] r[%ld](%ld) = (%f <= %f)\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.rd, res};
}

writeback_t fpu::fle_d() {
    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    uint64_t res = f64_le(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FLE_D] r[%ld](%ld) = (%f <= %f)\n", inst.rd, res, reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.rd, res};
}

writeback_t fpu::flt_s() {
    float32_t frs1 = { (uint32_t)inst.frs1 };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    uint64_t res = f32_lt(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FLT_S] r[%ld](%ld) = (%f < %f)\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.rd, res};
}

writeback_t fpu::flt_d() {
    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    uint64_t res = f64_lt(frs1, frs2);

    set_fp_exceptions();

    FPU_INFO("[FLT_D] r[%ld](%ld) = (%f < %f)\n", inst.rd, res, reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.rd, res};
}

writeback_t fpu::fsgnj_s() {
    uint32_t frs1 = (uint32_t)inst.frs1;
    uint32_t frs2 = (uint32_t)inst.frs2;
    uint32_t sign = frs2 & F32_SIGN;
    uint32_t res = (frs1 & ~F32_SIGN) | (sign & F32_SIGN);

    FPU_INFO("[FSGNJ_S] r[%ld](%f) = sgnj(%f, %f)\n", inst.rd, reg2f(res), reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.frd, (uint64_t)res};
}

writeback_t fpu::fsgnj_d() {
    uint64_t frs1 = (uint64_t)inst.frs1;
    uint64_t frs2 = (uint64_t)inst.frs2;
    uint64_t sign = frs2 & F64_SIGN;
    uint64_t res = (frs1 & ~F64_SIGN) | (sign & F64_SIGN);

    FPU_INFO("[FSGNJ_D] r[%ld](%f) = sgnj(%f, %f)\n", inst.rd, reg2d(res), reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.frd, res};
}

writeback_t fpu::fsgnjn_s() {
    uint32_t frs1 = (uint32_t)inst.frs1;
    uint32_t frs2 = (uint32_t)inst.frs2;
    uint32_t sign = (frs2 & F32_SIGN) ^ F32_SIGN;
    uint32_t res = (frs1 & ~F32_SIGN) | (sign & F32_SIGN);

    FPU_INFO("[FSGNJN_S] r[%ld](%f) = sgnjn(%f, %f)\n", inst.rd, reg2f(res), reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.frd, (uint64_t)res};
}

writeback_t fpu::fsgnjn_d() {
    uint64_t frs1 = (uint64_t)inst.frs1;
    uint64_t frs2 = (uint64_t)inst.frs2;
    uint64_t sign = (frs2 & F64_SIGN) ^ F64_SIGN;
    uint64_t res = (frs1 & ~F64_SIGN) | (sign & F64_SIGN);

    FPU_INFO("[FSGNJN_D] r[%ld](%f) = sgnjn(%f, %f)\n", inst.rd, reg2d(res), reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.frd, res};
}

writeback_t fpu::fsgnjx_s() {
    uint32_t frs1 = (uint32_t)inst.frs1;
    uint32_t frs2 = (uint32_t)inst.frs2;
    uint32_t sign = (frs2 & F32_SIGN) ^ (frs1 & F32_SIGN);
    uint32_t res = (frs1 & ~F32_SIGN) | (sign & F32_SIGN);

    FPU_INFO("[FSGNJX_S] r[%ld](%f) = sgnjx(%f, %f)\n", inst.rd, reg2f(res), reg2f(inst.frs1), reg2f(inst.frs2));

    return writeback_t {inst.frd, (uint64_t)res};
}

writeback_t fpu::fsgnjx_d() {
    uint64_t frs1 = (uint64_t)inst.frs1;
    uint64_t frs2 = (uint64_t)inst.frs2;
    uint64_t sign = (frs2 & F64_SIGN) ^ (frs1 & F64_SIGN);
    uint64_t res = (frs1 & ~F64_SIGN) | (sign & F64_SIGN);

    FPU_INFO("[FSGNJX_D] r[%ld](%f) = sgnjx(%f, %f)\n", inst.rd, reg2d(res), reg2d(inst.frs1), reg2d(inst.frs2));

    return writeback_t {inst.frd, res};
}

// word to float
writeback_t fpu::fmv_w_x() {
    uint32_t data = (uint32_t)inst.rs1;
    uint64_t res = (uint64_t)data;

    FPU_INFO("[FMV_W_X] r[%lx](%f) = 0x%x\n", inst.rd, reg2f(res), data);

    return writeback_t {inst.frd, res};
}

// float to word
writeback_t fpu::fmv_x_w() {
    uint32_t data = (uint32_t)inst.frs1;
    uint64_t res = sext32(data);

    FPU_INFO("[FMV_X_W] r[%lx](0x%lx) = %f\n", inst.rd, res, reg2f(data));

    return writeback_t {inst.rd, res};
}

// double word to double
writeback_t fpu::fmv_d_x() {
    uint64_t data = (uint64_t)inst.rs1;
    uint64_t res = data;

    FPU_INFO("[FMV_D_X] r[%lx](%f) = 0x%lx\n", inst.rd, reg2d(res), data);

    return writeback_t {inst.frd, res};
}

// double to double word
writeback_t fpu::fmv_x_d() {
    uint64_t data = (uint64_t)inst.frs1;
    uint64_t res = data;

    FPU_INFO("[FMV_X_D] r[%lx](0x%lx) = %f\n", inst.rd, res, reg2d(data));

    return writeback_t {inst.rd, res};
}

uint32_t fpu::get_rounding_mode() {
    uint32_t rm = inst.rm;

    if (rm == 7) {
        uint32_t frm = read_frm();
        if (frm <= 4) {
            rm = frm;
        } else {
            RVGPU_ERROR_PRINT("illegal instruction: %x\n", inst.bits);
        }
    } else if (rm > 4) {
        RVGPU_ERROR_PRINT("illegal instruction: %x\n", inst.bits);
    }

    return rm;
}

void fpu::set_fp_exceptions() {
    if (softfloat_exceptionFlags) {
        write_fflags(read_fflags() | softfloat_exceptionFlags);
    }
    softfloat_exceptionFlags = 0;
}

uint32_t fpu::read_fflags() {
    return fcsr & 0x1f;
}

void fpu::write_fflags(uint32_t data) {
    uint32_t mask = 0x1f;
    fcsr = (fcsr & (~mask)) | (data & mask);
}

uint32_t fpu::read_frm() {
    return (fcsr >> 5) & 0x7;
}

void fpu::write_frm(uint32_t data) {
    uint32_t mask = 0x7 << 5;
    fcsr = (fcsr & (~mask)) | ((data << 5) & mask);
}