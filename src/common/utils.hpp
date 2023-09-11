#pragma once

#include <bit>
#include <cstdint>

#define FOREACH_WARP_THREAD \
    for (uint32_t thread=0; thread<WARP_THREAD_N; thread++)

namespace utils {
    float reg2f(uint64_t data);
    uint64_t f2reg(float data);
    double reg2d(uint64_t data);
    uint64_t d2reg(double data);

    // convert float to integer
    float ui2f(uint32_t uidata);
    float ul2f(uint64_t uldata);
    double ul2d(uint64_t uldata);
    uint32_t f2ui(float fdata);
    uint64_t f2ul(float fdata);
    uint64_t d2ul(double ddata);
}