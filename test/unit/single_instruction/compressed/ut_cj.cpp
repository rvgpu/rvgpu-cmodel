#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_j) {
    test_instruction(0xa801, RES(reg::pc, GetInstAddr() + 16)); // 0xa801: c.j 16
    test_instruction(0xbfc5, RES(reg::pc, GetInstAddr() - 16)); // 0xbfc5: c.j -16
}