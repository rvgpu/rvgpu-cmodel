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
#include "vram/vram.hpp"

#include "rvgsim.h"
#include "rvgpu.hpp"

rvgsim::rvgsim() {
    m_gpu = new rvgpu();
    m_vram = new vram(VRAM_SIZE);
}

rvgsim::~rvgsim() {
    free(m_gpu);
    free(m_vram);
}

void rvgsim::write_doorbell(uint64_t addr, uint64_t data) {
}

uint64_t rvgsim::read_doorbell(uint64_t addr) {
    return 0;
}

void rvgsim::write_mmio(uint64_t addr, uint64_t data) {
    m_gpu->write_mmio(addr, data);
}

uint64_t rvgsim::read_mmio(uint64_t addr) {
    return m_gpu->read_mmio(addr);
}

void rvgsim::write_vram(uint64_t addr, uint64_t data, uint32_t size) {
    switch(size) {
    case 8:
        m_vram->write<uint64_t>(addr, data);
        break;
    case 4:
        m_vram->write<uint32_t>(addr, data);
        break;
    case 2:
        m_vram->write<uint16_t>(addr, data);
        break;
    case 1:
        m_vram->write<uint8_t>(addr, data);
        break;
    default:
        break;
    }
}

uint64_t rvgsim::read_vram(uint64_t addr, uint32_t size) {
    uint64_t ret = 0;

    switch(size) {
    case 8:
        ret = m_vram->read<uint64_t>(addr);
        break;
    case 4:
        ret = m_vram->read<uint32_t>(addr);
        break;
    case 2:
        ret = m_vram->read<uint16_t>(addr);
        break;
    case 1:
        ret = m_vram->read<uint8_t>(addr);
        break;
    default:
        break;
    }

    return ret;
}
