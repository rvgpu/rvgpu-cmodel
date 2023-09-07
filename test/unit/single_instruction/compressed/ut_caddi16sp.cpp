#include "ut_compressed.hpp"

TEST_F(ut_compressed, decode_and_execuate_caddi16sp) {
    check_caddi(0x6141, reg::sp, 0, GetStackPointer() + 16);     // 0x6141: c.addi16sp 16
    check_caddi(0x717d, reg::sp, 0, GetStackPointer() - 16);     // 0x717d: c.addi16sp -16
}