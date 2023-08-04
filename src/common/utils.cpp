#include <bit>
#include "utils.hpp"

float utils::reg2f(uint64_t data) {
    uint32_t data32 = data;
    return std::bit_cast<float>(data32);
}

uint64_t utils::f2reg(float data) {
    return uint64_t(std::bit_cast<uint32_t>(data));
}

float utils::ui32_to_f32(uint32_t data) {
    return (float)data;
}
