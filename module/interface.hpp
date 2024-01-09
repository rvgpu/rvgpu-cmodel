#pragma once
#include <cstdio>
#include <queue>

#include "module/module.hpp"

template <typename T>
class interface {
public:
    interface(rmodule *m) {
        m_m = m;
    }

    void write(T data) {
        m_connected->data.push(data);
        m_connected->m_m->signal();
    }

    T read() {
        T ret = data.front();
        data.pop();
        return ret;
    }

    void connect_to(interface *to_connect) {
        m_connected = to_connect;
        to_connect->connect_from(this);
    }

protected:
    void connect_from(interface *from_connect) {
        m_connected = from_connect;
    }

    interface *m_connected;
    std::queue<T> data;

    rmodule *m_m;
};