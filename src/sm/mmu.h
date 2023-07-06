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

#ifndef RVGSIM_MMU_H
#define RVGSIM_MMU_H

#include <cstdint>

class mmu_t {
public:
    template<class T> T load(uint64_t addr){
        return *((T*)(addr));
    }

    template<class T> void store(uint64_t addr, T data){
        *(T*)(addr + m_addr_high) = data;
    }

    void set_base_addr(uint64_t addr_high) {
        m_addr_high = addr_high;
    }
private:
    // used for rv32, sp etc. is 64 bit but register is 32 bit, should register the high 32 bit to m_addr_high
    // m_addr_high is 0 when use rv64;
    uint64_t m_addr_high = 0;
};
#endif //RVGSIM_MMU_H
