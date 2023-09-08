#include "ut_compressed.hpp"

TEST_F(ut_compressed, decode_and_execuate_c_addi16sp) {
    // c.addi16sp  ==>   addi sp, sp, imm
    check_addi(0x6141, make_pair(reg::sp, GetStackPointer()), make_pair(reg::sp, GetStackPointer() + 16)); // 0x6141: c.addi16sp 16
    check_addi(0x717d, make_pair(reg::sp, GetStackPointer()), make_pair(reg::sp, GetStackPointer() - 16)); // 0x6141: c.addi16sp 16
}