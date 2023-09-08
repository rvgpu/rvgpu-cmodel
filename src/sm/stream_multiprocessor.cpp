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
#include "top/command_stream.h"
#include "stream_multiprocessor.h"
#include "simt/simt.hpp"

void * sm::multithread_runner(void *arg) {
    sm *this_sm = (sm *)arg;

    while (1) {
        pthread_mutex_t *msg_list_mutex = this_sm->get_mutex();

        pthread_mutex_lock(msg_list_mutex);

        if (this_sm->has_msg()) {
            message msg = this_sm->get_msg();

            this_sm->run(msg);
            this_sm->send_response();
        }

        pthread_mutex_unlock(msg_list_mutex);
    }

    return nullptr;
}

sm::sm(int id, command_processor *cp) {
    m_id = id;
    m_cp = cp;
    m_simt = new simt();
    pthread_create(&m_thread, nullptr, multithread_runner, this);
}

sm::~sm() {
    delete m_simt;
    pthread_join(m_thread, nullptr);
}

void sm::run(message msg) {
    m_simt->setup(msg);
    m_simt->run();
}

bool sm::has_msg() {
    return m_cp->has_msg();
}

message sm::get_msg() {
    return m_cp->get_msg();
}

pthread_mutex_t * sm::get_mutex() {
    return m_cp->get_mutex();
}

void sm::send_response() {
    m_cp->receive_response();
    return;
}
