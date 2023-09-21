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

#include "noc/network_on_chip.hpp"

noc::noc() {
    pthread_mutex_init(&m_message_size_mutex, nullptr);

    for (int i = 0; i < SM_NUM; i++) {
        pthread_mutex_init(&m_message_mutex[i], nullptr);
    }
}

noc::~noc() {
    pthread_mutex_destroy(&m_message_size_mutex);

    for (int i = 0; i < SM_NUM; i++) {
        pthread_mutex_destroy(&m_message_mutex[i]);
    }
}

void noc::write_message_size(int msg_size) {
    pthread_mutex_lock(&m_message_size_mutex);
    m_message_size = msg_size;
    pthread_mutex_unlock(&m_message_size_mutex);
}

int noc::read_message_size() {
    int msg_size;

    pthread_mutex_lock(&m_message_size_mutex);
    msg_size = m_message_size;
    pthread_mutex_unlock(&m_message_size_mutex);

    return msg_size;
}

void noc::decrease_message_size() {
    pthread_mutex_lock(&m_message_size_mutex);
    m_message_size--;
    pthread_mutex_unlock(&m_message_size_mutex);
}

bool noc::message_size_is_zero() {
    bool result;

    pthread_mutex_lock(&m_message_size_mutex);
    result = (m_message_size == 0);
    pthread_mutex_unlock(&m_message_size_mutex);

    return result;
}

void noc::write_message(uint32_t sm_id, message msg){
    pthread_mutex_lock(&m_message_mutex[sm_id]);
    m_message[sm_id].push_back(msg);    
    pthread_mutex_unlock(&m_message_mutex[sm_id]);
}

message noc::read_message(uint32_t sm_id) {
    message msg = {};

    pthread_mutex_lock(&m_message_mutex[sm_id]);
    msg = m_message[sm_id].front();
    m_message[sm_id].pop_front();
    pthread_mutex_unlock(&m_message_mutex[sm_id]);

    return msg;
}

bool noc::has_message(uint32_t sm_id) {
    bool result;

    pthread_mutex_lock(&m_message_mutex[sm_id]);
    result = !m_message[sm_id].empty();
    pthread_mutex_unlock(&m_message_mutex[sm_id]);

    return result;
}
