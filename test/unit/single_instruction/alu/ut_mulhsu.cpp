#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64im_mul) {
    // 0x02c5a533       mulhsu    a0, a1, a2
    int64_t a, b;
    a = 0x1000000000;
    b = 0x2000000000;
    // result is 0x200 00000000 00000000
    test_instruction(0x02c5a533, IN(reg::a1, a), IN(reg::a2, b), RES(reg::a0, 0x200));
}