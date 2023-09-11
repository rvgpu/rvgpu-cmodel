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

union convert_data32 {
    uint32_t uidata;
    float fdata;
};

union convert_data64 {
    uint64_t uldata;
    double ddata;
};

float utils::ui2f(uint32_t uidata) {
    return std::bit_cast<float>(uidata);
}

float utils::ul2f(uint64_t uldata) {
    return ui2f(uint32_t(uldata));
}

uint32_t utils::f2ui(float fdata) {
    return std::bit_cast<uint32_t>(fdata);
}

uint64_t utils::f2ul(float fdata) {
    return uint64_t(f2ui(fdata));
}

double utils::ul2d(uint64_t uldata) {
    return std::bit_cast<double>(uldata);
}

uint64_t utils::d2ul(double ddata) {
    return std::bit_cast<uint64_t>(ddata);
}
