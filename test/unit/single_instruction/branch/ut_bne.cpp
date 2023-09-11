#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_bne) {
    // 0xfa0418e3 : bnez s0, -80 (bne s0, x0, -80)
    test_instruction(0xfa0418e3, IN(reg::s0, 1), RES(reg::pc, int64_t(single_inst) - 80));
    test_instruction(0xfa0418e3, IN(reg::s0, 0), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0xfa0418e3, IN(reg::s0, -1), RES(reg::pc, int64_t(single_inst) - 80));
    test_instruction(0xfa0418e3, IN(reg::s0, 12), RES(reg::pc, int64_t(single_inst) - 80));
    test_instruction(0xfa0418e3, IN(reg::s0, -12), RES(reg::pc, int64_t(single_inst) - 80));
}