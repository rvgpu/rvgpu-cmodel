#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_add) {
    // 0x40b50533        sub a0, a0, a1
    test_instruction(0x40b50533, IN(reg::a0, 2), IN(reg::a1, 1), RES(reg::a0, 1));
    test_instruction(0x40b50533, IN(reg::a0, 1), IN(reg::a1, 2), RES(reg::a0, -1));
    test_instruction(0x40b50533, IN(reg::a0, -1), IN(reg::a1, 1), RES(reg::a0, -2));
    test_instruction(0x40b50533, IN(reg::a0, -1), IN(reg::a1, 2), RES(reg::a0, -3));
    test_instruction(0x40b50533, IN(reg::a0, 1), IN(reg::a1, -1), RES(reg::a0, 2));
    test_instruction(0x40b50533, IN(reg::a0, 1), IN(reg::a1, -2), RES(reg::a0, 3));
}

TEST_F(ut_inst, decode_and_execute_rv64i_subw) {
    // 0x40b6063b   subw	a2, a2, a1
    test_instruction(0x40b6063b, IN(reg::a2, 2), IN(reg::a1, 1), RES(reg::a2, 1));
    test_instruction(0x40b6063b, IN(reg::a2, 1), IN(reg::a1, 2), RES(reg::a2, -1));
    test_instruction(0x40b6063b, IN(reg::a2, -1), IN(reg::a1, 1), RES(reg::a2, -2));
    test_instruction(0x40b6063b, IN(reg::a2, -1), IN(reg::a1, 2), RES(reg::a2, -3));
    test_instruction(0x40b6063b, IN(reg::a2, 1), IN(reg::a1, -1), RES(reg::a2, 2));
    test_instruction(0x40b6063b, IN(reg::a2, 1), IN(reg::a1, -2), RES(reg::a2, 3));
}