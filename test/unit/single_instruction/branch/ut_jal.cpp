#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_pseudo_j) {
    // 0x0380006f : j 56 (jal x0, 56)
    test_instruction(0x0380006f, RES(reg::pc, GetInstAddr() + 56));
}