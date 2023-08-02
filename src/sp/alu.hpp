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

#include "encoding.hpp"
#include "inst_issue.hpp"

class alu {
public:
    alu(uint32_t id);

    uint64_t run(inst_issue instruction);

private:
    uint32_t m_id;
    inst_issue inst;

    uint64_t add();
    uint64_t addi();
    uint64_t addiw();
    uint64_t addw();
    uint64_t lui();
    uint64_t mulw();
    uint64_t mul();
    uint64_t sltu();
    uint64_t slliw();
    uint64_t slli();
    uint64_t slt();
    uint64_t srli();
    uint64_t sub();
    uint64_t andi();
    uint64_t ori();
    uint64_t xori();
    uint64_t OR();
};