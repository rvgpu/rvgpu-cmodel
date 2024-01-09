#include <cstdio>
#include <pthread.h>
#include <cstdint>
#include <string>

#include "modules.hpp"

static void *rthread(void *arg) {
    modules *m = (modules *)arg;

    fflush(stdout);
    pthread_barrier_wait(&(m->m_barrier));

    while (1) {
        pthread_cond_wait(&m->m_cond, &m->m_mutex);
        
        while (m->has_signal()) {
            m->runner();
            m->signal_out();
        }

        if (m->is_shutdown()) {
            break;
        }
    }

    fflush(stdout);

    return NULL;
}

modules::modules(std::string name) {
    m_name = name;

    shutdown = false;
    m_signal_count = 0;
    pthread_barrier_init(&m_barrier, NULL, 2);
    pthread_cond_init(&m_cond, NULL);
    pthread_mutex_init(&m_mutex, NULL);
    pthread_mutex_init(&m_shutdown_mutex, NULL);
    pthread_mutex_init(&m_signal_count_mutex, NULL);

    pthread_create(&m_thread, NULL, rthread, this);

    // 等待创建的子线程同步
    pthread_barrier_wait(&m_barrier);
}

modules::~modules() {
    // 如果还有未结束的信号，继续执行完成
    if (has_signal()) {
        pthread_cond_signal(&m_cond);
    }

    // 结束子进行
    pthread_mutex_lock(&m_shutdown_mutex);
    shutdown = true;
    pthread_mutex_unlock(&m_shutdown_mutex);
    pthread_cond_signal(&m_cond);

    pthread_join(m_thread, NULL);
}

void modules::signal(void ) {
    signal_in();
    pthread_cond_signal(&m_cond);
}

bool modules::has_signal() {
    bool ret = false;
    pthread_mutex_lock(&m_signal_count_mutex);
    ret = (m_signal_count != 0);
    pthread_mutex_unlock(&m_signal_count_mutex);

    return ret;
}

void modules::signal_in() {
    pthread_mutex_lock(&m_signal_count_mutex);
    m_signal_count ++;
    pthread_mutex_unlock(&m_signal_count_mutex);
}

void modules::signal_out() {
    pthread_mutex_lock(&m_signal_count_mutex);
    m_signal_count --;
    pthread_mutex_unlock(&m_signal_count_mutex);
}

bool modules::is_shutdown() {
    bool ret = false;
    pthread_mutex_lock(&m_shutdown_mutex);
    ret = (shutdown == true);
    pthread_mutex_unlock(&m_shutdown_mutex);
    return ret;
}