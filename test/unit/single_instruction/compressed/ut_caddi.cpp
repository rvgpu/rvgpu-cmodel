#include "ut_compressed.hpp"

TEST_F(ut_compressed, decode_and_execuate_caddi) {
    check_caddi(0x1141, reg::sp, 0, GetStackPointer() - 16);   // 0x1141: addi    sp, sp, -16
    check_caddi(0x07c1, reg::a5, 2, 2 + 16); // 0x07c1: addi a5, a5, 16
}