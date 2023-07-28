#include <bit>
#include "common/softfloat_types.h"

float32_t f32_mulAdd(float32_t a, float32_t b, float32_t c) {
    float float_a = std::bit_cast<float>(a.v);
    float float_b = std::bit_cast<float>(b.v);
    float float_c = std::bit_cast<float>(c.v);
    float float_d = float_a * float_b + float_c;

    float32_t result = { std::bit_cast<uint32_t>(float_d) };

    return result;
}