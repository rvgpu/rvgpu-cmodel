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

#include "vram/vram.hpp"
#include "noc/network_on_chip.hpp"
#include "simt/simt.hpp"
#include "stream_multiprocessor.hpp"

void * sm::multithread_runner(void *arg) {
    sm *this_sm = (sm *)arg;

    while (1) {
        if (this_sm->has_msg()) {
            message msg = this_sm->get_msg();
            this_sm->run(msg);
            this_sm->send_response();
        }
    }

    return nullptr;
}

sm::sm(uint32_t id, vram *rvgpu_vram, noc* connector) {
    m_id = id;
    m_noc = connector;
    m_simt = new simt(rvgpu_vram);
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
    return m_noc->has_message(m_id);
}

message sm::get_msg() {
    return m_noc->read_message(m_id);
}

void sm::send_response() {
    m_noc->decrease_message_size();
}
