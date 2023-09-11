#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_beq) {
    // 0xfa0506e3 : beqz a0, -84 (beq a0, x0, -84)
    test_instruction(0xfa0506e3, IN(reg::a0, 1), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0xfa0506e3, IN(reg::a0, 0), RES(reg::pc, int64_t(single_inst) - 84));
    test_instruction(0xfa0506e3, IN(reg::a0, -1), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0xfa0506e3, IN(reg::a0, 12), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0xfa0506e3, IN(reg::a0, -12), RES(reg::pc, int64_t(single_inst) + 4));
}