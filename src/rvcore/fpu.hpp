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

#include "inst_issue.hpp"

class fpu {
public:
    fpu(uint32_t id);

    writeback_t run(inst_issue instruction);
private:
    uint32_t m_id;
    inst_issue inst;
    uint32_t fcsr = 0;  // Floating-Point Control and Status Register (FCSR)

    uint32_t get_rounding_mode();
    void set_fp_exceptions();
    uint32_t read_fflags();
    void write_fflags(uint32_t data);
    uint32_t read_frm();
    void write_frm(uint32_t data);


    writeback_t fadd_s();
    writeback_t fadd_d();
    writeback_t fsub_s();
    writeback_t fsub_d();
    writeback_t fmul_s();
    writeback_t fmul_d();
    writeback_t fdiv_s();
    writeback_t fdiv_d();
    writeback_t fmadd_s();
    writeback_t fmadd_d();
    writeback_t fmsub_s();
    writeback_t fmsub_d();
    writeback_t fnmadd_s();
    writeback_t fnmadd_d();
    writeback_t fnmsub_s();
    writeback_t fnmsub_d();
    writeback_t fmax_s();
    writeback_t fmax_d();
    writeback_t fmin_s();
    writeback_t fmin_d();
    writeback_t fsqrt_s();
    writeback_t fsqrt_d();
    writeback_t fcvt_s_l();
    writeback_t fcvt_s_lu();
    writeback_t fcvt_s_w();
    writeback_t fcvt_s_wu();
    writeback_t fcvt_l_s();
    writeback_t fcvt_lu_s();
    writeback_t fcvt_w_s();
    writeback_t fcvt_wu_s();
    writeback_t fcvt_d_l();
    writeback_t fcvt_d_lu();
    writeback_t fcvt_d_w();
    writeback_t fcvt_d_wu();
    writeback_t fcvt_l_d();
    writeback_t fcvt_lu_d();
    writeback_t fcvt_w_d();
    writeback_t fcvt_wu_d();
    writeback_t feq_s();
    writeback_t feq_d();
    writeback_t fle_s();
    writeback_t fle_d();
    writeback_t flt_s();
    writeback_t flt_d();
    writeback_t fsgnj_s();
    writeback_t fsgnj_d();
    writeback_t fsgnjn_s();
    writeback_t fsgnjn_d();
    writeback_t fsgnjx_s();
    writeback_t fsgnjx_d();
    writeback_t fmv_w_x();
    writeback_t fmv_x_w();
    writeback_t fmv_d_x();
    writeback_t fmv_x_d();
};