#ifndef RVGSIM_MATH_HPP
#define RVGSIM_MATH_HPP

#include <cstdint>

uint32_t ftou(float  in) {
    return *(uint32_t*)&in;
}

uint32_t int_to_float(int32_t in) {
    auto inf = (float)in;
    return *(uint32_t *)&inf;
}

uint32_t fmul(uint32_t in1, uint32_t in2) {
    float res = (*(float *)&in1) * (*(float*)&in2);
    return *(uint32_t *)&res;
}
#endif //RVGSIM_MATH_HPP
