#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_or) {
    //bits: 0x00a5e533     #or  a0, a1, a0
    test_instruction(0x00a5e533, IN(reg::a1, 4), IN(reg::a0, 1), RES(reg::a0, 1 | 4));
}