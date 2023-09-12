#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_bnez) {
    test_instruction(0xe901, IN(reg::a0, 0), RES(reg::pc, GetInstAddr() + 2));    // 0xe901: c.bnez a0, 16
    test_instruction(0xe901, IN(reg::a0, 1), RES(reg::pc, GetInstAddr() + 16));    // 0xe901: c.bnez a0, 16
    test_instruction(0xf965, IN(reg::a0, 0), RES(reg::pc, GetInstAddr() + 2));    // 0xf965: c.bnez a0, -16
    test_instruction(0xf965, IN(reg::a0, 1), RES(reg::pc, GetInstAddr() - 16));    // 0xf965: c.bnez a0, -16
}