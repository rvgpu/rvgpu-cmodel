#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_add) {
    // 0x952e: c.add a0, a1  ==> c.add a0, a0, a1
    test_instruction(0x952e, IN(reg::a0, 0x12345678), IN(reg::a1, 0x87654321), RES(reg::a0, 0x12345678 + 0x87654321));
}