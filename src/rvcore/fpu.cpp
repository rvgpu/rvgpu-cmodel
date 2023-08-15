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
    float32_t frs3 = { (uint32_t)inst.frs3 ^ (1 << 31) };
    float32_t res = f32_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FMSUB_S] r[%ld](%f) = %f * %f - %f\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fmsub_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t frs3 = { (uint64_t)inst.frs3 ^ (1L << 63) };
    float64_t res = f64_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FMSUB_D] r[%ld](%f) = %f * %f - %f\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2), reg2d(inst.frs3));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fnmadd_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 ^ (1 << 31) };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t frs3 = { (uint32_t)inst.frs3 ^ (1 << 31) };
    float32_t res = f32_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FNMADD_S] r[%ld](%f) = -(%f * %f + %f)\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fnmadd_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 ^ (1L << 63) };
    float64_t frs2 = { (uint64_t)inst.frs2 };
    float64_t frs3 = { (uint64_t)inst.frs3 ^ (1L << 63) };
    float64_t res = f64_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FNMADD_D] r[%ld](%f) = -(%f * %f + %f)\n", inst.rd, reg2d(res.v), reg2d(inst.frs1), reg2d(inst.frs2), reg2d(inst.frs3));

    return writeback_t {inst.frd, res.v};
}

writeback_t fpu::fnmsub_s() {
    softfloat_roundingMode = get_rounding_mode();

    float32_t frs1 = { (uint32_t)inst.frs1 ^ (1 << 31) };
    float32_t frs2 = { (uint32_t)inst.frs2 };
    float32_t frs3 = { (uint32_t)inst.frs3 };
    float32_t res = f32_mulAdd(frs1, frs2, frs3);

    set_fp_exceptions();

    FPU_INFO("[FNMSUB_S] r[%ld](%f) = -(%f * %f - %f)\n", inst.rd, reg2f(res.v), reg2f(inst.frs1), reg2f(inst.frs2), reg2f(inst.frs3));

    return writeback_t {inst.frd, (uint64_t)res.v};
}

writeback_t fpu::fnmsub_d() {
    softfloat_roundingMode = get_rounding_mode();

    float64_t frs1 = { (uint64_t)inst.frs1 ^ (1L << 63) };
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

writeback_t fpu::fle_s() {
    uint64_t res;
    res = f32_le(float32_t(inst.frs1), float32_t(inst.frs2));
    FPU_INFO("[FLE_S] r[%lx](%ld) = (%f <= %f)\n", inst.rd, res, reg2f(inst.frs1), reg2f(inst.frs2));
    return writeback_t {inst.rd, res};
}

writeback_t fpu::fmv_w_x() {
    float res = reg2f(inst.rs1);
    FPU_INFO("[FMV_W_X] r[%lx](%f) = %f\n", inst.rd, res, reg2f(inst.rs1));
    return writeback_t {inst.frd, f2reg(res)};
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