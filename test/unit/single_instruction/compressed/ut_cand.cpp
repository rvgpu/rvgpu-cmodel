#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_addi) {
    // 0x8d6d: c.and a0, a1  ==> and a0, a0, a1
    test_instruction(0x8d6d, IN(reg::a0, 0x1234), IN(reg::a1, 0x5678), RES(reg::a0, (0x1234) & (0x5678)));
    test_instruction(0x8d6d, IN(reg::a0, 0x87475856), IN(reg::a1, 0x8981d84), RES(reg::a0, (0x87475856) & (0x8981d84)));
}