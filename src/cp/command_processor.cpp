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

#include "common/message.h"
#include "common/configs.h"
#include "command_processor.h"

command_processor::command_processor() {
}

void command_processor::run(uint64_t cmds, std::vector<message> &msg) {
    rvgpu_command *cs = (rvgpu_command *)cmds;
    switch (cs->type) {
        case RVGPU_COMMAND_TYPE_1D:
            command_split_1d(cs, msg);
            break;
        case RVGPU_COMMAND_TYPE_2D:
            // command_split_2d(cs, msg);
            break;
        default:
            printf("COMMAND TYPE TODO\n");
            break;
    }
}

void command_processor::command_split_1d(rvgpu_command *cs, std::vector<message> &msgs) {
    int32_t tcount = cs->range.x;
    uint32_t start = 0;

    while (tcount > 0) {
        message msg = {};
        msg.target = 0;
        msg.shader = cs->shader;
        msg.start = start;
        if (tcount > 16) {
            msg.count = 16;
        } else {
            msg.count = tcount;
        }

        tcount = tcount - msg.count;

        msgs.push_back(std::move(msg));
    }
}
