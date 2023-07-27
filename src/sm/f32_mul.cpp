#include "common/softfloat_types.h"

float32_t f32_mul(float32_t a, float32_t b) {
    float float_a = *((float *)(&(a.v)));
    float float_b = *((float *)(&(b.v)));
    float float_c = float_a * float_b;

    float32_t result = { *((uint32_t *)(&float_c)) };

    return result;
}