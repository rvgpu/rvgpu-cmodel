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

#include "common/configs.h"
#include "common/debug.hpp"

#include "vram/vram.hpp"
#include "mmu/mmu.hpp"
#include "noc/network_on_chip.hpp"
#include "command_processor.hpp"

command_processor::command_processor(vram *rvgpu_vram, mmu *rvgpu_mmu, noc* connector) {
    m_vram = rvgpu_vram;
    m_mmu = rvgpu_mmu;
    m_noc = connector;
}

command_processor::~command_processor() {
}

void command_processor::run(uint64_t cmds) {
    rvgpu_command cmd;
    cmd.dim.x = m_vram->read<uint32_t>(m_mmu->find_pa(cmds + 0));
    cmd.dim.y = m_vram->read<uint32_t>(m_mmu->find_pa(cmds + 4));
    cmd.dim.z = m_vram->read<uint32_t>(m_mmu->find_pa(cmds + 8));
    cmd.program.pointer         = m_vram->read<uint32_t>(m_mmu->find_pa(cmds + 16));
    cmd.program.stack_pointer   = m_vram->read<uint32_t>(m_mmu->find_pa(cmds + 24));
    cmd.program.argsize         = m_vram->read<uint32_t>(m_mmu->find_pa(cmds + 32));    
    for (uint32_t i=0; i<cmd.program.argsize; i++) {
        cmd.program.args[i]     = m_vram->read<uint32_t>(m_mmu->find_pa(cmds + 40 + i*8));
    }

    for (uint32_t sz=0; sz<cmd.dim.z; sz+=1) {
        // Split Z
        for (uint32_t sy=0; sy<cmd.dim.y; sy+=1) {
            // Split Y
            command_split_1d(cmd.dim.x, cmd.program);
        }
    }
}

void command_processor::command_split_1d(uint32_t splitx, program_t prog) {
    m_noc->write_message_size((splitx - 1) / 16 + 1);

    uint32_t tcount = splitx;
    uint32_t start = 0;
    uint32_t sm_id = 0;

    while (tcount > 0) {
        message msg = {};

        msg.target = sm_id;
        msg.shader = prog;
        msg.shader.stack_pointer += sm_id * SM_STACK_SIZE;
        msg.start = start;
        if (tcount > 16) {
            msg.count = 16;
        } else {
            msg.count = tcount;
        }

        m_noc->write_message(sm_id, msg);

        start += 16;
        tcount = tcount - msg.count;
        sm_id = (sm_id + 1) % SM_NUM;
    }
}

bool command_processor::finished() {
    return m_noc->message_size_is_zero();
}
