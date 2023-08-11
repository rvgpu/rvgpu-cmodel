#pragma once

#include <cstdint>

static inline uint64_t proc_mulhu(uint64_t a, uint64_t b)
{
    uint64_t t;
    uint32_t y1, y2, y3;
    uint64_t a0 = (uint32_t)a, a1 = a >> 32;
    uint64_t b0 = (uint32_t)b, b1 = b >> 32;

    t = a1*b0 + ((a0*b0) >> 32);
    y1 = t;
    y2 = t >> 32;

    t = a0*b1 + y1;

    t = a1*b1 + y2 + (t >> 32);
    y2 = t;
    y3 = t >> 32;

    return ((uint64_t)y3 << 32) | y2;
}

inline static int64_t proc_mulh(int64_t a, int64_t b)
{
    int negate = (a < 0) != (b < 0);
    uint64_t res = proc_mulhu(a < 0 ? -a : a, b < 0 ? -b : b);
    return negate ? ~res + (a * b == 0) : res;
}

inline static uint64_t proc_mulhsu(int64_t a, uint64_t b)
{
    int negate = a < 0;
    uint64_t res = proc_mulhu(a < 0 ? -a : a, b);
    return negate ? ~res + (a * b == 0) : res;
}