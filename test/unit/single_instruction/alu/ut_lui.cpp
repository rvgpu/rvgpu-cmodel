#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_lui) {
    // 0x02000e93 : lui x29, 2
    test_instruction(0x00002eb7, RES(reg::x29, 0x2000));
}