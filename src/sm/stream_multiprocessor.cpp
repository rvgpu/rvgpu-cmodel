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
#include "common/command_stream.h"
#include "stream_multiprocessor.h"

sm::sm() {
    auto isa_parser = new isa_parser_t("RV64IMAFD");
    m_sp = new stream_processor();
    p = new compute_unit(isa_parser);
    sp = (uint32_t*) malloc(5000 * sizeof (uint32_t));
    sp = sp + 2000;
}

void sm::run_vs(message msg) {
    printf("[SM] receive message VS: %d %d\n", msg.shader.start, msg.shader.count);

    m_sp->setup(msg.shader);
    m_sp->run();
}

void sm::run_fs(message msg) {
    message_tile tile = msg.tile;
    for (uint32_t x=tile.x; x<tile.w; x+=4) {
        for (uint32_t y=tile.y; y<tile.h; y+=4) {
            message_shader shader = msg.shader;
            shader.start = (uint64_t(y) << 32) + x;
            shader.count = 16;
            shader.xstride = 2;
            shader.argcount = 3;
            // shader.args[0]
            // shader.args[1] =     xy
            shader.args[2] = (1UL << 32) + 0; // v1v0
            shader.args[3] = 2;
            m_sp->setup(shader);
            m_sp->run();
        }
    }
}

void sm::run(message msg) {
    switch(msg.msg) {
        case CMD_MESSAGE_START_CU_VS:
            run_vs(msg);
            break;
        case CMD_MESSAGE_START_FS:
            run_fs(msg);
            break;
        default:
            break;
    }
}
