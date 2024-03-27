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

#include <cstdlib>
#include "common/debug.hpp"

#include "rvgsim.h"

rvgsim::rvgsim() {
}

rvgsim::~rvgsim() {
}

void rvgsim::write_doorbell(uint64_t addr, uint64_t data) {
    printf("write doorbell[0x%lx]: 0x%lx\n", addr, data);
}

uint64_t rvgsim::read_doorbell(uint64_t addr) {
    printf("read doorbell[0x%lx]\n", addr);
    return 0;
}

void rvgsim::write_mmio(uint64_t addr, uint64_t data) {
    printf("write mmio[0x%lx]: 0x%lx\n", addr, data);
}

uint64_t rvgsim::read_mmio(uint64_t addr) {
    printf("read mmio[0x%lx]\n", addr);
    return 0;
}

void rvgsim::write_vram(uint64_t addr, uint64_t data, uint32_t size) {
    printf("write vram[0x%lx]: 0x%lx\n", addr, data);
}

uint64_t rvgsim::read_vram(uint64_t addr, uint32_t size) {
    printf("read vram[0x%lx]\n", addr);
    return 0;
}
