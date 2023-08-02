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
#include <stdint.h>

#include "common/configs.h"
#include "common/utils.hpp"

class register_file {
public:
    register_file() {
        FOREACH_WARP_THREAD {
            ireg[thread][0] = 0;
        }
    };

    void write_ireg(uint32_t tid, uint32_t rid, uint64_t data) {
        if (rid != 0) {
            ireg[tid][rid] = data;
        }
    }

    uint64_t read_ireg(uint32_t tid, uint32_t rid) {
        if (rid > 32) { return 0; }
        return ireg[tid][rid];
    }

    void write_freg(uint32_t tid, uint32_t rid, uint64_t data) {
        freg[tid][rid] = data;
    }

    uint64_t read_freg(uint32_t tid, uint32_t rid) {
        return freg[tid][rid];
    }

private:
    uint64_t ireg[WARP_THREAD_N][32];
    uint64_t freg[WARP_THREAD_N][32];
};