#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_addw) {
    // 0x00e5053b : addw a0, a0, a4
    test_instruction(0x00e5053b, IN(reg::a0, 11), IN(reg::a4, 12), RES(reg::a0, 11 + 12));
    test_instruction(0x00e5053b, IN(reg::a0, -11), IN(reg::a4, 12), RES(reg::a0, -11 + 12));
    test_instruction(0x00e5053b, IN(reg::a0, 11), IN(reg::a4, -12), RES(reg::a0, 11 - 12));
    test_instruction(0x00e5053b, IN(reg::a0, 11), IN(reg::a4, 0), RES(reg::a0, 11 + 0));
    test_instruction(0x00e5053b, IN(reg::a0, 0), IN(reg::a4, 12), RES(reg::a0, 0 + 12));
}