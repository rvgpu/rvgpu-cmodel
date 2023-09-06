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

warp::warp(register_file *reg) {
    m_reg = reg;
    m_dec = new dec();
    m_branch = new branch();
}

void warp::setup(message msg) {
    pc = msg.shader.pointer;
    startpc = msg.shader.pointer;
    lanes.reset();
    stops.set();

    RVGPU_DEBUG_PRINT("WARP Start from %d to %d\n", msg.start, msg.start + msg.count);
    for (uint32_t i=0; i<WARP_THREAD_N; i++) {
        if (i < msg.count) {
            lanes.set(i);
            stops.reset(i);

            m_reg->write(i, uint64_t(reg::s0), 0);
            m_reg->write(i, uint64_t(reg::ra), 0);

            RVGPU_DEBUG_PRINT("[SP][WARP0.%d] setup sp: 0x%lx\n", i, msg.shader.stack_pointer + 0x1000 * i);
            m_reg->write(i, uint64_t(reg::sp), msg.shader.stack_pointer + 0x1000 * i);

            RVGPU_DEBUG_PRINT("[SP][WARP0.%d] setup a0(tid): 0x%x\n", i, msg.start + i);
            m_reg->write(i, uint64_t(reg::a0), msg.start + i);
            for (uint32_t argi=1; argi<msg.shader.argsize; argi++) {
                RVGPU_DEBUG_PRINT("[SP][WARP0.%d] setup a%d(arg[%d]): 0x%lx\n", i, argi, argi, msg.shader.args[argi]);
                m_reg->write(i, uint64_t(reg::a0) + argi, msg.shader.args[argi]);
            }
        }
    }

    RVGPU_DEBUG_PRINT("[SP][WARP0] setup lanes: %lx\n", lanes.to_ulong());
    RVGPU_DEBUG_PRINT("[SP][WARP0] setup stops: %lx\n", stops.to_ulong());
}

inst_issue warp::schedule() {
    uint32_t instcode = *((uint32_t *)pc);
    RVGPU_DEBUG_PRINT("Fetch inst: [%lx (0x%lx)] 0x%08x\n", (uint64_t(pc) - uint64_t(startpc)), pc, instcode);
    uint8_t pc_step = IS_COMPRESSED_INST(instcode) ? 2 : 4;
    inst_issue to_issue = m_dec->decode_inst(instcode);
    to_issue.lanes = lanes.to_ulong();
    to_issue.currpc = pc;

    if (to_issue.type == encoding::INST_TYPE_BRANCH) {
        FOREACH_WARP_THREAD {
            if (lanes.test(thread)) {
                m_reg->register_stage(thread, to_issue);
                writeback_t wb = m_branch->run(to_issue, npc[thread]);
                m_reg->write(thread, wb.rid, wb.wdata);
            }
        }

        struct warpstore torun = diverage();
        lanes = torun.lanes;
        pc = torun.pc;
        to_issue.type = encoding::INST_TYPE_NOP;
        to_issue.lanes = lanes.to_ulong();
    } else {
        pc = pc + pc_step;
    }

    return to_issue;
}

warpstore warp::diverage() {
    warpstore split0 = {0};
    warpstore split1 = {0};
    warpstore pop = {0};

    FOREACH_WARP_THREAD {
        if (lanes.test(thread)) {
            if ((pc + 4) != npc[thread]) {
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

bool warp::merge_lanes(struct warpstore &w0, struct warpstore &w1) {
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

bool warp::stop() {
    if (stops.all()) {
        return true;
    }

    if (pc == 0) {
        if (warpstack.empty()) {
            return true;
        } else {
            warpstore torun = warpstack.top();
            warpstack.pop();
            lanes = torun.lanes;
            pc = torun.pc;
            return false;
        }
    }

    return false;
}
