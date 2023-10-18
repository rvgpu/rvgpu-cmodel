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

#include "mmu.hpp"
#include "vram/vram.hpp"

#define _BITS(bits, pos, width) (((bits) >> (pos)) & ((1ULL << (width)) - 1Ull))

mmu::mmu(vram *rvgpu_vram) {
    m_vram = rvgpu_vram;

    // Page table
    PT_BASE = 0x00100000;
}

uint64_t mmu::lookup_page_table(uint64_t pt_base, uint64_t index) {
    uint64_t pt_entry = m_vram->read<uint64_t>(pt_base + index * 8);

    if (pt_entry == 0) {
        printf("Page not found\n");
        return 0;
    } else {
        return pt_entry;
    }
}

uint64_t mmu::mmu_trans(uint64_t va) {
    uint64_t level1 = lookup_page_table(PT_BASE, _BITS(va, 39, 9));
    uint64_t level2 = lookup_page_table(level1, _BITS(va, 30, 9));
    uint64_t level3 = lookup_page_table(level2, _BITS(va, 21, 9));

    uint64_t level3_index = _BITS(va, 12, 9);
    uint64_t level3_entry = m_vram->read<uint64_t>(level3 + level3_index * 8);

    if (level3_entry == 0) {
        printf("Page not found\n");
        return 0;
    } else {
        return level3_entry + _BITS(va, 0, 12);
    }
}