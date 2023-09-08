#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_addi) {
    test_instruction(0x1141, std::make_pair(reg::sp, GetSP()), std::make_pair(reg::sp, ref::addi(GetSP(), -16))); // 0x1141: addi    sp, sp, -16
    test_instruction(0x07c1, std::make_pair(reg::a5, 2), std::make_pair(reg::a5, ref::addi(2, 16)));   // 0x07c1: c.addi a5, 16 ==> addi a5, a5, 16
}