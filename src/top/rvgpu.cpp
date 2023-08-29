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

#include "vram/vram.hpp"
#include "sm/stream_multiprocessor.h"
#include "cp/command_processor.h"
#include "common/configs.h"

#include "command_stream.h"
#include "rvgpu.h"

rvgpu::rvgpu() {
    m_vram = new vram(VRAM_SIZE);
    m_cp = new command_processor();
    m_sm = new sm();

    regs = (uint32_t *)malloc(MBYTE(2));
}

void rvgpu::run(uint64_t cmds) {
    std::vector<message> msg;
    m_cp->run(cmds, msg);

    for (auto m : msg) {
        m_sm->run(m);
    }
}

void rvgpu::write_register(uint64_t addr, uint32_t data) {
    regs[addr] = data;
}

uint32_t rvgpu::read_register(uint64_t addr) {
    return regs[addr];
}

void rvgpu::write_vram(uint64_t addr, uint64_t data, uint32_t size) {
    switch (size) {
    case 8:
        m_vram->write<uint64_t>(addr, uint64_t(data));
        break;
    case 4:
        m_vram->write<uint32_t>(addr, uint32_t(data));
        break;
    case 2:
        m_vram->write<uint16_t>(addr, uint16_t(data));
        break;
    case 1:
        m_vram->write<uint8_t>(addr, uint8_t(data));
        break;
    default:
        RVGPU_ERROR_PRINT("[TOP] write rvgpu.vram with error size: %d\n", size);
        break;
    }
}

uint64_t rvgpu::read_vram(uint64_t addr, uint32_t size) {
    uint64_t rdata = 0;

    switch (size) {
    case 8:
        rdata = (uint64_t)m_vram->read<uint64_t>(addr);
        break;
    case 4:
        rdata = (uint64_t)m_vram->read<uint32_t>(addr);
        break;
    case 2:
        rdata = (uint64_t)m_vram->read<uint16_t>(addr);
        break;
    case 1:
        rdata = (uint64_t)m_vram->read<uint8_t>(addr);
        break;
    default:
        RVGPU_ERROR_PRINT("[TOP] read rvgpu.vram with error size: %d\n", size);
        break;
    }

    return rdata;
}