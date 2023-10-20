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

#include "common/utils.hpp"
#include "simt.hpp"
#include "mmu/mmu.hpp"
#include "rvcore/encoding.hpp"

simt::simt(vram *rvgpu_vram) {
    m_mmu = new mmu(rvgpu_vram);
    m_reg = new register_file();
    m_warp = new warp(rvgpu_vram, m_mmu, m_reg);
    m_ls = new load_store(rvgpu_vram, m_mmu);
    for (uint32_t i=0; i<WARP_THREAD_N; i++) {
        m_alu[i] = new alu(i);
        m_fpu[i] = new fpu(i);
    }
}

void simt::setup(message msg) {
    m_warp->setup(msg);
}

void simt::issue_single(inst_issue to_issue, uint32_t tid) {
    writeback_t wb = {};
    switch (to_issue.type) {
        case encoding::INST_TYPE_ALU: {
            wb = m_alu[tid]->run(to_issue);
            break;
        }
        case encoding::INST_TYPE_FPU: {
            wb = m_fpu[tid]->run(to_issue);
            break;
        }
        case encoding::INST_TYPE_LS: {
            wb = m_ls->run(to_issue);
            break;
        }
        case encoding::INST_TYPE_NOP: {
            break;
        }
        default:
            RVGPU_ERROR_PRINT("Instruction ERROR: %x\n", to_issue.bits);
            break;
    }

    m_reg->write(tid, wb.rid, wb.wdata);
}

void simt::issue(inst_issue to_issue) {
    FOREACH_WARP_THREAD {
        if (to_issue.lanes & (1 << thread)) {
            m_reg->register_stage(thread, to_issue);
            issue_single(to_issue, thread);
        }
    }
}

void simt::run() {
    while (!m_warp->stop()) {
        inst_issue to_issue = m_warp->schedule();

        issue(to_issue);
    }
}