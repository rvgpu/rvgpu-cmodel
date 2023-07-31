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

#include "common/message.h"

#include "warp.hpp"
#include "register_file.hpp"
#include "alu.hpp"
#include "fpu.hpp"
#include "load_store.hpp"
#include "decoder.hpp"

class ut_insns;
// Stream Processor: A simt-x processor

class stream_processor {
public:
    stream_processor();
    void setup(uint64_t shader, uint64_t argument, uint64_t globalid, uint32_t tcount);
    void run(void);

private:
    warp            *m_warp;
    dec             *m_dec;
    register_file   *m_reg;
    alu             *m_alu;
    fpu             *m_fpu;
    load_store      *m_ls;

    uint64_t        stack_pointer;
    uint64_t        pc;

    uint64_t execuator(inst_issue inst);
    uint64_t branch(inst_issue inst);

    friend ut_insns;
};
