#ifndef RVGSIM_MATH_HPP
#define RVGSIM_MATH_HPP

#include <cstdint>

uint32_t int_to_float(int32_t in) {
    auto inf = (float)in;
    return *(uint32_t *)&inf;
}
#endif //RVGSIM_MATH_HPP
