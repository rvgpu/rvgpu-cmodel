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
#ifndef RVGSIM_TYPE_HPP
#define RVGSIM_TYPE_HPP
struct inst_issue{
    uint64_t lanes;
    uint32_t bits;
    uint64_t currpc;
    virtual ~inst_issue()=default;
};

struct writeback_t {
    uint64_t rid;
    uint64_t wdata;
    uint64_t pc;
    writeback_t() {rid = 0; wdata = 0; pc = 0;}
    writeback_t(uint64_t reg_id, uint64_t data) { rid = reg_id; wdata = data; pc = 0;}
    virtual ~writeback_t()=default;
};

#endif //RVGSIM_TYPE_HPP
