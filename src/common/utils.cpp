#include <bit>
#include "utils.hpp"

float utils::reg2f(uint64_t data) {
    uint32_t data32 = data;
    return std::bit_cast<float>(data32);
}

uint64_t utils::f2reg(float data) {
    return uint64_t(std::bit_cast<uint32_t>(data));
}

double utils::reg2d(uint64_t data) {
    return std::bit_cast<double>(data);
}

uint64_t utils::d2reg(double data) {
    return std::bit_cast<uint64_t>(data);
}