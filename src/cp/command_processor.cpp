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
    uint64_t pa = m_mmu->find_pa(cmds);
    uint32_t type = m_vram->read<uint32_t>(pa);

    switch (type) {
        case RVGPU_COMMAND_TYPE_1D:
            command_split_1d(cmds);
            break;
        case RVGPU_COMMAND_TYPE_2D:
            command_split_2d(cmds);
            break;
        default:
            RVGPU_ERROR_PRINT("COMMAND TYPE TODO\n");
            break;
    }
}

void command_processor::command_split_1d(uint64_t cmds) {
    uint64_t pa = m_mmu->find_pa(cmds);

    // rvgpu_command_type type
    pa += 8;

    uint64_t shader_pointer = m_vram->read<uint64_t>(pa);
    pa += 8;

    uint64_t shader_stack_pointer = m_vram->read<uint64_t>(pa);
    pa += 8;

    uint32_t shader_argsize = m_vram->read<uint32_t>(pa);
    pa += 8;

    uint64_t shader_args[8];

    for (uint32_t i = 0; i < 8; i++) {
        shader_args[i] = m_vram->read<uint64_t>(pa);
        pa += 8;
    }

    program_t shader;
    shader.pointer = shader_pointer;
    shader.stack_pointer = shader_stack_pointer;
    shader.argsize = shader_argsize;
    for (uint32_t i = 0; i < 8; i++) {
        shader.args[i] = shader_args[i];
    }

    uint32_t range_x = m_vram->read<uint32_t>(pa);

    m_noc->write_message_size((range_x - 1) / 16 + 1);

    uint32_t tcount = range_x;
    uint32_t start = 0;
    uint32_t sm_id = 0;

    while (tcount > 0) {
        message msg = {};

        msg.target = sm_id;
        msg.shader = shader;
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

void command_processor::command_split_2d(uint64_t cmds) {
    uint64_t pa = m_mmu->find_pa(cmds);

    // rvgpu_command_type type
    pa += 8;

    uint64_t shader_pointer = m_vram->read<uint64_t>(pa);
    pa += 8;

    uint64_t shader_stack_pointer = m_vram->read<uint64_t>(pa);
    pa += 8;

    uint32_t shader_argsize = m_vram->read<uint32_t>(pa);
    pa += 8;

    uint64_t shader_args[8];

    for (uint32_t i = 0; i < 8; i++) {
        shader_args[i] = m_vram->read<uint64_t>(pa);
        pa += 8;
    }

    program_t shader;
    shader.pointer = shader_pointer;
    shader.stack_pointer = shader_stack_pointer;
    shader.argsize = shader_argsize;
    for (uint32_t i = 0; i < 8; i++) {
        shader.args[i] = shader_args[i];
    }

    uint32_t range_x = m_vram->read<uint32_t>(pa);
    pa += 4;
    uint32_t range_y = m_vram->read<uint32_t>(pa);

    m_noc->write_message_size(range_y * ((range_x - 1) / 16 + 1));

    uint32_t tcount_x = range_x;
    uint32_t tcount_y = range_y;
    uint32_t sm_id = 0;

    while (tcount_y > 0) {
        tcount_x = range_x;
        sm_id = 0;

        while(tcount_x > 0) {
            message msg = {};

            msg.target = sm_id;
            msg.shader = shader;
            msg.shader.stack_pointer += sm_id * SM_STACK_SIZE;
            msg.start = (range_y - tcount_y) * range_x + (range_x - tcount_x);
            if (tcount_x > 16) {
                msg.count = 16;
            } else {
                msg.count = tcount_x;
            }

            m_noc->write_message(sm_id, msg);

            tcount_x = tcount_x - msg.count;
            sm_id = (sm_id + 1) % SM_NUM;
        }

        tcount_y = tcount_y - 1;
    }
}

bool command_processor::finished() {
    return m_noc->message_size_is_zero();
}
