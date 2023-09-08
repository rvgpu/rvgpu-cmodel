#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_srli) {
    test_instruction(0x8105, std::make_pair(reg::a0, 0x1234), std::make_pair(reg::a0, 0x1234 >> 1)); // 0x8111: c.srli a0, 1 ==> srli a0, a0, 1
    test_instruction(0x8109, std::make_pair(reg::a0, 0x1234), std::make_pair(reg::a0, 0x1234 >> 2)); // 0x8111: c.srli a0, 2 ==> srli a0, a0, 2
    test_instruction(0x810d, std::make_pair(reg::a0, 0x1234), std::make_pair(reg::a0, 0x1234 >> 3)); // 0x8111: c.srli a0, 3 ==> srli a0, a0, 3
    test_instruction(0x8111, std::make_pair(reg::a0, 0x1234), std::make_pair(reg::a0, 0x1234 >> 4)); // 0x8111: c.srli a0, 4 ==> srli a0, a0, 4
    test_instruction(0x8185, std::make_pair(reg::a1, 0x1234), std::make_pair(reg::a1, 0x1234 >> 1)); // 0x8185: c.srli a1, 1 ==> srli a1, a1, 1
}