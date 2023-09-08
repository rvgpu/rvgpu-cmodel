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

#include "command_processor.h"
#include "common/debug.hpp"

command_processor::command_processor() {
    m_message_size = 0;
    pthread_mutex_init(&m_message_mutex, nullptr);
}

command_processor::~command_processor() {
    pthread_mutex_destroy(&m_message_mutex);
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

    pthread_mutex_lock(&m_message_mutex);

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

        start += 16;
        tcount = tcount - msg.count;

        m_message.push_back(std::move(msg));
    }

    m_message_size = m_message.size();

    pthread_mutex_unlock(&m_message_mutex);
}

bool command_processor::has_msg() {
    return m_message_size > 0;
}

message command_processor::get_msg() {
    message msg = m_message.front();
    m_message.pop_front();
    return msg;
}

pthread_mutex_t * command_processor::get_mutex() {
    return &m_message_mutex;
}

void command_processor::receive_response() {
    m_message_size--;
    return;
}

bool command_processor::finished() {
    return m_message_size == 0;
}
