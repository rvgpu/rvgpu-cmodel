#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_andi) {
    // 0x8905: c.andi a0, 1  ==> andi a0, a0, 1
    // 0x890d: c.andi a0, 3  ==> andi a0, a0, 3
    // 0x891d: c.andi a0, 7  ==> andi a0, a0, 7

    test_instruction(0x8905, IN(reg::a0, 15), RES(reg::a0, 15 & 0x1));
    test_instruction(0x890d, IN(reg::a0, 15), RES(reg::a0, 15 & 0x3));
    test_instruction(0x891d, IN(reg::a0, 15), RES(reg::a0, 15 & 0x7));
}