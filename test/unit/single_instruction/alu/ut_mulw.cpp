#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64im_mulw) {
    // 0x03da8c3b : mulw s8, s5, t4
    int64_t a, b;
    a = 2;
    b = 1;
    test_instruction(0x03da8c3b, IN(reg::s5, a), IN(reg::t4, b), RES(reg::s8, a * b));
    a = 1;
    b = 2;
    test_instruction(0x03da8c3b, IN(reg::s5, a), IN(reg::t4, b), RES(reg::s8, a * b));
    a = -11;
    b = 12;
    test_instruction(0x03da8c3b, IN(reg::s5, a), IN(reg::t4, b), RES(reg::s8, a * b));
    a = 11;
    b = -12;
    test_instruction(0x03da8c3b, IN(reg::s5, a), IN(reg::t4, b), RES(reg::s8, a * b));
    a = -11;
    b = -12;
    test_instruction(0x03da8c3b, IN(reg::s5, a), IN(reg::t4, b), RES(reg::s8, a * b));
}