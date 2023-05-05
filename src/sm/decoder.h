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

#ifndef RVGSIM_DECODER_H
#define RVGSIM_DECODER_H

#include <cstdint>
#include <cstring>

typedef uint64_t insn_bits_t;
#define insn_length(x) \
  (((x) & 0x03) < 0x03 ? 2 : \
   ((x) & 0x1f) < 0x1f ? 4 : \
   ((x) & 0x3f) < 0x3f ? 6 : \
   8)

#define STATE (*cu->get_state())
#define sext_xlen(x) (((sreg_t)(x) << (64 - xlen)) >> (64 - xlen))
#define WRITE_RD(value) WRITE_REG((insn.rd() | cu->ext_rd()), value)
#define WRITE_REG(reg, value) ({ CHECK_REG(reg); STATE.XPR.write(reg, value); })
#define CHECK_REG(reg) ((void) 0)
#define READ_REG(reg) ({ CHECK_REG(reg); STATE.XPR[reg]; })

class insn_t {
public:
    insn_t() = default;
    explicit insn_t(insn_bits_t bits) : b(bits) {}

    [[nodiscard]] insn_bits_t bits() const { return b; }

    int64_t u_imm() { return int64_t(xs(12, 20) << 12); }
    uint64_t rd() { return x(7, 5); }

private:
    insn_bits_t b;

    [[nodiscard]] uint64_t xs(int lo, int len) const { return int64_t(b) << (64 - lo - len) >> (64 - len); }
    [[nodiscard]] uint64_t x(int lo, int len) const { return (b >> lo) & ((insn_bits_t(1) << len) - 1); }
};

template<class T, size_t N, bool zero_reg>
class regfile_t {
public:
    void write(size_t i, T value) {
        if (!zero_reg || i != 0)
            data[i] = value;
    }

    const T &operator[](size_t i) const {
        return data[i];
    }

    regfile_t() {
        reset();
    }

    void reset() {
        memset(data, 0, sizeof(data));
    }

private:
    T data[N];
};

#endif //RVGSIM_DECODER_H
