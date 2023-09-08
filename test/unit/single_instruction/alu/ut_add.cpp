#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_add) {
    //0x00d786b3 : add a3, a5, a3
    test_instruction(0x00d786b3, IN(reg::a5, 1), IN(reg::a3, 2), RES(reg::a3, 1 + 2));
}