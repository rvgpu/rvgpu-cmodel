#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_jal) {
    test_instruction(0x2801, RES(reg::pc, GetInstAddr() + 16));    // 0x2801: cjal 16
    test_instruction(0x3fc5, RES(reg::pc, GetInstAddr() - 16));    // 0x3fc5: c.jal -16
}