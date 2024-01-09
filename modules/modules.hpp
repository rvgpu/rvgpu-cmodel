#pragma once

#include <cstdio>
#include <pthread.h>
#include <cstdint>
#include <string>

class modules {
public:
    modules(std::string name);
    ~modules();

    // 和线程信号相关的函数
    void signal(void );
    bool has_signal();
    void signal_in();
    void signal_out();
    bool is_shutdown();

    virtual void runner(void) {};

    // 用于多线程的变量
    pthread_t m_thread;
    pthread_barrier_t m_barrier;
    pthread_cond_t m_cond;
    pthread_mutex_t m_mutex;
private:
    void *m_connected;

    // 唤醒信号的个数
    uint32_t m_signal_count;
    pthread_mutex_t m_signal_count_mutex;
    bool shutdown;
    pthread_mutex_t m_shutdown_mutex;
    
    // 模块的属性
    std::string m_name;
};