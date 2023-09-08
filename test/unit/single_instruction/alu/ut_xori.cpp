#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_xori) {
    // 0x001aca93 : xori s5, s5, 1
    test_instruction(0x001aca93, IN(reg::s5, 7), RES(reg::s5, 6));
}