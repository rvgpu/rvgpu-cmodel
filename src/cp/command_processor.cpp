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

#include "noc/network_on_chip.h"
#include "command_processor.h"

command_processor::command_processor() {
}

command_processor::~command_processor() {
}

void command_processor::communicate_with(noc *noc_comm) {
    m_noc = noc_comm;
}

void command_processor::run(uint64_t cmds) {
    rvgpu_command *cs = (rvgpu_command *)cmds;
    switch (cs->type) {
        case RVGPU_COMMAND_TYPE_1D:
            command_split_1d(cs);
            break;
        case RVGPU_COMMAND_TYPE_2D:
            // command_split_2d(cs);
            break;
        default:
            RVGPU_ERROR_PRINT("COMMAND TYPE TODO\n");
            break;
    }
}

void command_processor::command_split_1d(rvgpu_command *cs) {
    int32_t tcount = cs->range.x;
    uint32_t start = 0;
    uint32_t sm_id = 0;

    m_noc->write_message_size((tcount - 1) / 16 + 1);

    while (tcount > 0) {
        message msg = {};

        msg.target = sm_id;
        msg.shader = cs->shader;
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
