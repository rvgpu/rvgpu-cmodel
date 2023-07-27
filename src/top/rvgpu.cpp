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

#include "common/command_stream.h"
#include "common/message.h"

#include "rvgpu.h"

rvgpu::rvgpu() {
    m_sm = new sm();
}

void rvgpu::run(uint64_t cmd) {
    command_stream *cs = (command_stream *)cmd;
    std::vector<message> msg;
    if (cs->type == CS_TYPE_VS) {
        command_stream_vs vs = cs->cmd.vs;

        for (uint32_t i=0; i<vs.vertex_count; i++) {  // one vertex on one sm now
            message tmsg = {};
            tmsg.target = 0; // message send to sm[0]
            tmsg.msg = CMD_MESSAGE_START_CU_VS;
            tmsg.shader = cs->shader;
            tmsg.start = i;
            tmsg.count = 1;
            tmsg.desc = vs.desc;
            msg.push_back(std::move(tmsg));
        }
    }

    for (auto m : msg) {
        m_sm->run(m);
    }
}
