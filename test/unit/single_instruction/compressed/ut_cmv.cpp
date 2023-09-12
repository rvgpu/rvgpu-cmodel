#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_mv) {
    // 0x852e: c.mv a0, a1 ==> add a0, a1, x0
    test_instruction(0x852e, IN(reg::a1, 0x12345678), RES(reg::a0, 0x12345678));
}