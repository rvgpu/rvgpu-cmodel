#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_addi16sp) {
    // c.addi16sp  ==>   addi sp, sp, imm
    test_instruction(0x6141, std::make_pair(reg::sp, GetSP()), std::make_pair(reg::sp, ref::addi(GetSP(), 16))); // 0x6141: c.addi16sp 16
    test_instruction(0x717d, std::make_pair(reg::sp, GetSP()), std::make_pair(reg::sp, ref::addi(GetSP(), -16))); // 0x717d: c.addi16sp -16
}