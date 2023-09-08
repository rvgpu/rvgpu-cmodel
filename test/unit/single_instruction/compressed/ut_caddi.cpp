#include "ut_compressed.hpp"

TEST_F(ut_compressed, decode_and_execuate_c_addi) {
    check_addi(0x1141, make_pair(reg::sp, GetStackPointer()), make_pair(reg::sp, GetStackPointer() - 16)); // 0x1141: addi    sp, sp, -16
    check_addi(0x07c1, make_pair(reg::a5, 2), make_pair(reg::a5, 2 + 16)); // 0x07c1: c.addi a5, 16 ==> addi a5, a5, 16
}