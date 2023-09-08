#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64im_mul) {
    // 0x02a59633       mulh    a2, a1, a0
    int64_t a = 0x1000000000;
    int64_t b = 0x2000000000;
    // 0x200 00000000 00000000
    test_instruction(0x02a59633, IN(reg::a1, a), IN(reg::a0, b), RES(reg::a2, 0x200));
}