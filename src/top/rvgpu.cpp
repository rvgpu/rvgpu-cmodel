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

#include "common/debug.hpp"

#include "rvgpu.hpp"

rvgpu::rvgpu() {
    // internal noc here

    init_mmio();
}

rvgpu::~rvgpu() {
}

void rvgpu::write_mmio(uint64_t addr, uint64_t data) {
    write_reg32(addr, data);
}

uint64_t rvgpu::read_mmio(uint64_t addr) {
    return read_reg32(addr);
}

void rvgpu::init_mmio(void) {
    write_reg32(REGOFF(mmRCC_CONFIG_MEMSIZE), (VRAM_SIZE >> 20));
}

void rvgpu::write_reg32(uint64_t addr, uint32_t data) {
    uint32_t *regptr = (uint32_t *)(&m_regs[addr]);
    *regptr = data;
}

uint32_t rvgpu::read_reg32(uint64_t addr) {
    uint32_t *regptr = (uint32_t *)(&m_regs[addr]);
    return *regptr;
}
