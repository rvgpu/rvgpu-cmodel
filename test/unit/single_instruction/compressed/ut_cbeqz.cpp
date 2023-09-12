#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_beqz) {
    test_instruction(0xc901, IN(reg::a0, 1), RES(reg::pc, GetInstAddr() + 2));    // 0xc901: c.beqz a0, 16
    test_instruction(0xc901, IN(reg::a0, 0), RES(reg::pc, GetInstAddr() + 16));    // 0xc901: c.beqz a0, 16
    test_instruction(0xd965, IN(reg::a0, 1), RES(reg::pc, GetInstAddr() + 2));    // 0xd965: c.beqz a0, -16
    test_instruction(0xd965, IN(reg::a0, 0), RES(reg::pc, GetInstAddr() - 16));    // 0xd965: c.beqz a0, -16
}