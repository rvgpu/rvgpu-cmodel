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
#include "rvcore/rvcore.hpp"
#include "simt.hpp"
#include "rvcore/encoding.hpp"

simt::simt(vram *rvgpu_vram, mmu *rvgpu_mmu) {
    m_core = new riskvcore(rvgpu_vram, rvgpu_mmu);
    m_warp = new warp(rvgpu_vram, rvgpu_mmu, m_core);
}

void simt::setup(message msg) {
    m_warp->setup(msg);
}

void simt::issue(inst_issue to_issue) {
    FOREACH_WARP_THREAD {
        if (to_issue.lanes & (1 << thread)) {
            m_core->get_operand(thread, to_issue);
            writeback_t res = m_core->exe(to_issue, thread);
            m_core->write_back(thread, res);
        }
    }
}

void simt::run() {
    while (!m_warp->stop()) {
        inst_issue to_issue = m_warp->schedule();
        issue(to_issue);
    }
}