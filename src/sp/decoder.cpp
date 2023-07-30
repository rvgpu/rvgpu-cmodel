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

#include "decoder.hpp"

#define IN_DECODER
#include "encoding.hpp"

dec::dec() {

}

inst_issue dec::decode_inst(uint32_t instcode) {
    inst_issue to_issue;

    to_issue.bits = instcode;
    to_issue.code = encoding::match(instcode);
    to_issue.type = to_issue.code & encoding::INST_TYPE_MASK;

    bits = instcode;
    to_issue.rd = xget(7, 5);
    to_issue.rs1_id = xget(15, 5);
    to_issue.rs2_id = xget(20, 5);
    to_issue.rs3_id = xget(27, 5);

    to_issue.u_imm = int64_t(xsget(12, 20) << 12);
    to_issue.i_imm = int64_t(xsget(20, 12));
    to_issue.s_imm = xget(7, 5) + (xsget(25, 7) << 5);
    to_issue.sb_imm = (xget(8, 4) << 1) + (xget(25, 6) << 5) + (xget(7, 1) << 11) + (imm_sign() << 12);
    to_issue.uj_imm = (xget(21, 10) << 1) + (xget(20, 1) << 11) + (xget(12, 8) << 12) + (imm_sign() << 20);

    return to_issue;
}