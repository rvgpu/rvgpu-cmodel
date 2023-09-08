#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_srli) {
    test_instruction(0x8105, IN(reg::a0, 0x1234), RES(reg::a0, 0x1234 >> 1)); // 0x8111: c.srli a0, 1 ==> srli a0, a0, 1
    test_instruction(0x8109, IN(reg::a0, 0x1234), RES(reg::a0, 0x1234 >> 2)); // 0x8111: c.srli a0, 2 ==> srli a0, a0, 2
    test_instruction(0x810d, IN(reg::a0, 0x1234), RES(reg::a0, 0x1234 >> 3)); // 0x8111: c.srli a0, 3 ==> srli a0, a0, 3
    test_instruction(0x8111, IN(reg::a0, 0x1234), RES(reg::a0, 0x1234 >> 4)); // 0x8111: c.srli a0, 4 ==> srli a0, a0, 4
    test_instruction(0x8185, IN(reg::a1, 0x1234), RES(reg::a1, 0x1234 >> 1)); // 0x8185: c.srli a1, 1 ==> srli a1, a1, 1
}