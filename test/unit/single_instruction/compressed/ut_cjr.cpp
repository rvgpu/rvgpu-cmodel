#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_jr) {
    // 0x8502: c.jr a0  ==> jr a0
    test_instruction(0x8502, IN(reg::a0, 0x1234), RES(reg::pc, 0x1234));
}