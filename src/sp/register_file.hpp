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

class register_file {
public:
    register_file() {
        ireg[0][0] = 0;
    };

    template<typename T>
    void write_ireg(uint32_t warp, uint32_t id, T data) {
        if (id != 0) {
            uint64_t regaddr = (uint64_t) &(ireg[warp][id]);
            *(T *) regaddr = data;
        }
    }

    uint64_t read_ireg(uint32_t warp, uint32_t id) {
        if (id > 32) { return 0; }
        return ireg[warp][id];
    }

    void write_freg(uint32_t warp, uint32_t id, uint64_t data) {
        freg[warp][id] = data;
    }

    uint64_t read_freg(uint32_t warp, uint32_t id) {
        if (id > 32) { return 0; }
        return freg[warp][id];
    }

private:
    uint64_t ireg[1][32];
    uint64_t freg[1][32];
};