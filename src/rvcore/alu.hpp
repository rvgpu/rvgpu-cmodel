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

#include "common/debug.hpp"
#include "encoding.hpp"
#include "inst_issue.hpp"

class alu {
public:
    alu(uint32_t id);

    writeback_t run(inst_issue instruction);

private:
    uint32_t m_id;
    inst_issue inst;
    uint32_t xlen;

    writeback_t add();
    writeback_t addi();
    writeback_t addiw();
    writeback_t addw();
    writeback_t AND();
    writeback_t div();
    writeback_t divu();
    writeback_t divw();
    writeback_t divuw();
    writeback_t lui();
    writeback_t mulw();
    writeback_t mulh();
    writeback_t mulhsu();
    writeback_t mulhu();
    writeback_t mul();
    writeback_t sltu();
    writeback_t sll();
    writeback_t slliw();
    writeback_t slli();
    writeback_t sllw();
    writeback_t slt();
    writeback_t slti();
    writeback_t sltiu();
    writeback_t srl();
    writeback_t srli();
    writeback_t srliw();
    writeback_t srlw();
    writeback_t sra();
    writeback_t srai();
    writeback_t sraiw();
    writeback_t sraw();
    writeback_t sub();
    writeback_t subw();
    writeback_t andi();
    writeback_t ori();
    writeback_t XOR();
    writeback_t xori();
    writeback_t OR();
};