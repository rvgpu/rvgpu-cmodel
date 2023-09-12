#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_jalr) {
    // 0x9502: c.jalr a0  ==> jalr x1, a0, 0
    test_instruction(0x9502, IN(reg::a0, 0x1234), RES(reg::pc, 0x1234));
    test_instruction(0x9502, IN(reg::a0, 0x1234), RES(reg::x1, GetInstAddr() + 2));
}