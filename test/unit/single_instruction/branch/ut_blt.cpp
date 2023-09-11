#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_bltu) {
    // 0x00b54864 : blt a0, a1, 16
    test_instruction(0x00b54863, IN(reg::a0, 1), IN(reg::a1, 2), RES(reg::pc, int64_t(single_inst) + 16));
    test_instruction(0x00b54863, IN(reg::a0, 2), IN(reg::a1, 2), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0x00b54863, IN(reg::a0, 3), IN(reg::a1, 2), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0x00b54863, IN(reg::a0, 2), IN(reg::a1, 0), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0x00b54863, IN(reg::a0, 0), IN(reg::a1, 2), RES(reg::pc, int64_t(single_inst) + 16));
    test_instruction(0x00b54863, IN(reg::a0, 0), IN(reg::a1, 0), RES(reg::pc, int64_t(single_inst) + 4));
}