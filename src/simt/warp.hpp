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

#include <cstdint>
#include <bitset>
#include <stack>

#include "top/command_stream.h"
#include "common/configs.h"
#include "vram/vram.hpp"
#include "mmu/mmu.hpp"
#include "rvcore/inst_issue.hpp"
#include "rvcore/decoder.hpp"
#include "rvcore/branch.hpp"
#include "rvcore/register_file.hpp"


class ut_branch;
class mcore;

struct warpstore {
    uint64_t pc;
    std::bitset<WARP_THREAD_N> lanes;
};

class warp {
public:
    warp (vram *rvgpu_vram, mmu *simt_mmu, mcore *c);

    void setup(message msg);
    bool stop();

    inst_issue schedule();

private:
    vram *m_vram;
    mmu *m_mmu;
    register_file *m_reg;
    decoder *m_dec;
    branch *m_branch;
    mcore   *m_core;
    uint64_t startpc;
    uint64_t pc;
    uint64_t npc[WARP_THREAD_N];
    std::stack<struct warpstore> warpstack;
    std::bitset<WARP_THREAD_N> lanes;
    std::bitset<WARP_THREAD_N> stops;

    warpstore diverage();
    bool merge_lanes(struct warpstore &w0, struct warpstore &w1);

    friend ut_branch;
};