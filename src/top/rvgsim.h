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

#include "common/configs.h"
#include "top/command_stream.h"

class vram;
class noc;
class command_processor;
class sm;

class rvgsim{
public:
    rvgsim();
    ~rvgsim();

    void run(uint64_t cmd);
    void run_with_vram(uint64_t cmd);

    // Interface of register and vram
    void write_vram(uint64_t addr, uint64_t data, uint32_t size);
    uint64_t read_vram(uint64_t addr, uint32_t size);
    void write_register(uint64_t addr, uint32_t data);
    uint32_t read_register(uint64_t addr);
private:
    vram *m_vram;
    noc *m_noc;
    command_processor *m_cp;
    sm *m_sm[SM_NUM];
    uint32_t *regs;
};
