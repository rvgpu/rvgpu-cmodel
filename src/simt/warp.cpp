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

#include <cstdio>
#include <cassert>

#include "common/utils.hpp"
#include "common/regid.hpp"
#include "common/debug.hpp"
#include "warp.hpp"
#include "rvcore/rvcore.hpp"

warp_manager::warp_manager(vram *rvgpu_vram, mmu *simt_mmu, mcore *c) {
    m_vram = rvgpu_vram;
    m_mmu = simt_mmu;
    m_core = c;
}

void warp_manager::setup(message msg) {
    m_pc = msg.shader.pointer;
    startpc = msg.shader.pointer;
    lanes.reset();
    stops.set();

    RVGPU_DEBUG_PRINT("WARP Start from %d to %d\n", msg.start, msg.start + msg.count);
    for (uint32_t i=0; i<WARP_THREAD_N; i++) {
        if (i < msg.count) {
            lanes.set(i);
            stops.reset(i);
        }
    }
    m_core->register_setup(msg);

    RVGPU_DEBUG_PRINT("[SP][WARP0] setup lanes: %lx\n", lanes.to_ulong());
    RVGPU_DEBUG_PRINT("[SP][WARP0] setup stops: %lx\n", stops.to_ulong());
}


warp_status warp_manager::schedule(uint32_t inst) {
    RVGPU_DEBUG_PRINT("[%06lx] 0x%08x ==> \n", (uint64_t(pc) - uint64_t(startpc)), instcode);

    warp_status warp_issued = {};

    warp_issued.bits = inst;
    warp_issued.lanes = lanes;
    warp_issued.pc = m_pc;

    return warp_issued;
}

warp_status warp_manager::diverage() {
    warp_status split0 = {0};
    warp_status split1 = {0};
    warp_status pop = {0};

    FOREACH_WARP_THREAD {
        if (lanes.test(thread)) {
            if ((m_pc + 4) != npc[thread]) {
                split1.pc = npc[thread];
                split1.lanes.set(thread);
            } else {
                split0.pc = npc[thread];
                split0.lanes.set(thread);
            }
        }
    }

    if (!warpstack.empty()) {
        pop = warpstack.top();
        warpstack.pop();
    }

    if (merge_lanes(split0, split1)) {
        if (merge_lanes(split0, pop)) {
            return split0;
        } else {
            warpstack.push(pop);
            return split0;
        }
    } else if (merge_lanes(split0, pop)) {
        warpstack.push(split1);
        return split0;
    } else if (merge_lanes(split1, pop)) {
        warpstack.push(split0);
        return split1;
    } else {
        warpstack.push(pop);
        warpstack.push(split1);
        return split0;
    }
}

bool warp_manager::merge_lanes(struct warp_status &w0, struct warp_status &w1) {
    auto stopflip = stops;
    stopflip.flip();

    if (w0.lanes.none()) {
        w0.lanes = w1.lanes;
        w0.pc = w1.pc;

        return true;
    }

    if (w1.lanes.none()) {
        return true;
    }

    if (w0.pc == w1.pc) {
        w0.lanes = w0.lanes.operator|=(w1.lanes);
        w0.lanes = w0.lanes.operator&=(stopflip);
        return true;
    } else {
        return false;
    }
}

bool warp_manager::stop() {
    if (stops.all()) {
        return true;
    }

    if (m_pc == 0) {
        if (warpstack.empty()) {
            return true;
        } else {
            warp_status torun = warpstack.top();
            warpstack.pop();
            lanes = torun.lanes;
            m_pc = torun.pc;
            return false;
        }
    }

    return false;
}

void warp_manager::update_status(uint32_t tid, uint64_t thread_pc) {
    npc[tid] = thread_pc;
}

void warp_manager::update_status(uint64_t next_pc, std::bitset<WARP_THREAD_N> active_lanes) {
    m_pc = next_pc;
    lanes = active_lanes;
}

uint32_t warp_manager::fetch_inst(uint64_t pc) {
    uint64_t pc_pa = m_mmu->find_pa(pc);
    return m_vram->read<uint32_t>(pc_pa);
}

uint64_t warp_manager::get_pc() {
    return m_pc;
}



