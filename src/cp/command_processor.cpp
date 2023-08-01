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
        case RVGPU_COMMAND_TYPE_VS:
            command_vs(cs, msg);
            break;
        case RVGPU_COMMAND_TYPE_FS:
            command_fs(cs, msg);
            break;
        default:
            printf("COMMAND TYPE TODO\n");
            break;
    }
}

void command_processor::command_vs(rvgpu_command *cs, std::vector<message> &msg) {
    rvgpu_command_vs vs = cs->cmd.vs;

    uint32_t vcount = vs.vertex_count;
    uint32_t start = 0;

    while(vcount != 0) {
        uint32_t issue_count = 0;
        issue_count = ((vcount-1) >> WARP_THREAD_N_LOG2) ? (WARP_THREAD_N - 1) : ((vcount-1) & WARP_THREAD_N_MASK);

        message tmsg = {};
        tmsg.target = 0; // message send to sm[0]
        tmsg.msg = CMD_MESSAGE_START_CU_VS;
        tmsg.shader = vs.shader;
        tmsg.start = start;
        tmsg.count = issue_count + 1;
        tmsg.layout = vs.layout;
        tmsg.stack_pointer = vs.stack_pointer;
        msg.push_back(std::move(tmsg));

        start = start + issue_count + 1;
        vcount = vcount - issue_count - 1;
    }
}

void command_processor::command_fs(rvgpu_command *cs, std::vector<message> &msg) {
}
