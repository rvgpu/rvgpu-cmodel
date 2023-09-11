#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_addi) {
    // 0x8d0d: c.sub a0, a1  ==> sub a0, a0, a1
    test_instruction(0x8d0d, IN(reg::a0, 2), IN(reg::a1, 1), RES(reg::a0, 1));
    test_instruction(0x8d0d, IN(reg::a0, 2), IN(reg::a1, 2), RES(reg::a0, 0));
    test_instruction(0x8d0d, IN(reg::a0, 2), IN(reg::a1, 3), RES(reg::a0, -1));
    test_instruction(0x8d0d, IN(reg::a0, -1), IN(reg::a1, -1), RES(reg::a0, 0));
    test_instruction(0x8d0d, IN(reg::a0, -1), IN(reg::a1, 0), RES(reg::a0, -1));
    test_instruction(0x8d0d, IN(reg::a0, -1), IN(reg::a1, 1), RES(reg::a0, -2));
}