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

#include "common/configs.h"
#include "common/utils.hpp"
#include "common/regid.hpp"

class register_file {
public:
    register_file() {
        FOREACH_WARP_THREAD {
            reg[thread][0] = 0;
        }
    };

    void register_stage(uint32_t tid, inst_issue &to_issue) {
        to_issue.rs1 = read(tid, to_issue.rs1_id);
        to_issue.rs2 = read(tid, to_issue.rs2_id);
        to_issue.rs3 = read(tid, to_issue.rs3_id);
        to_issue.frs1 = read(tid, to_issue.frs1_id);
        to_issue.frs2 = read(tid, to_issue.frs2_id);
        to_issue.frs3 = read(tid, to_issue.frs3_id);
        to_issue.sreg = sreg_read(tid, to_issue.sreg_id);
    }

    uint64_t read(uint32_t tid, uint32_t rid) {
        return reg[tid][rid];
    }

    void write(uint32_t tid, uint32_t rid, uint64_t data) {
        if (rid != 0) {
            reg[tid][rid] = data;
        }
    }

    reg_t sreg_read(uint32_t tid, special_reg rid) {
        return m_sreg[tid][static_cast<uint32_t>(rid)];
    }

private:
    uint64_t reg[WARP_THREAD_N][64] = {};
    //special register
    reg_t m_sreg[WARP_THREAD_N][14] = {};
};