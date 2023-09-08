#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_li) {
    // c.li ==> addi rd, x0, imm
    test_instruction(0x4541, IN(reg::x0, 0), RES(reg::a0, 16));  // 0x4541: c.li a0, 16
    test_instruction(0x5541, IN(reg::x0, 0), RES(reg::a0, -16)); // 0x4541: c.li a0, -16
}