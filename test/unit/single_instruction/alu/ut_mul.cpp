#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64im_mul) {
    // 0x02b50533 : mul	a0, a0, a1
    int64_t a, b;
    a = 2; b = 1;
    test_instruction(0x02b50533, IN(reg::a0, a), IN(reg::a1, b), RES(reg::a0, a * b));
    a = 1; b = 2;
    test_instruction(0x02b50533, IN(reg::a0, a), IN(reg::a1, b), RES(reg::a0, a * b));
    a = -11; b = 12;
    test_instruction(0x02b50533, IN(reg::a0, a), IN(reg::a1, b), RES(reg::a0, a * b));
    a = 11; b = -12;
    test_instruction(0x02b50533, IN(reg::a0, a), IN(reg::a1, b), RES(reg::a0, a * b));
    a = -11; b = -12;
    test_instruction(0x02b50533, IN(reg::a0, a), IN(reg::a1, b), RES(reg::a0, a * b));
}

TEST_F(ut_inst, decode_and_execute_rv64im_mulh) {
    // 0x02a59633       mulh    a2, a1, a0
    int64_t a = 0x1000000000;
    int64_t b = 0x2000000000;
    // 0x200 00000000 00000000
    test_instruction(0x02a59633, IN(reg::a1, a), IN(reg::a0, b), RES(reg::a2, 0x200));
}

TEST_F(ut_inst, decode_and_execute_rv64im_mulsu) {
    // 0x02c5a533       mulhsu    a0, a1, a2
    int64_t a, b;
    a = 0x1000000000;
    b = 0x2000000000;
    // result is 0x200 00000000 00000000
    test_instruction(0x02c5a533, IN(reg::a1, a), IN(reg::a2, b), RES(reg::a0, 0x200));
}

TEST_F(ut_inst, decode_and_execute_rv64im_mulhu) {
    // 0x02c5b533       mulhu    a0, a1, a2
    int64_t a, b;
    a = 0x1000000000;
    b = 0x2000000000;
    // result is 0x200 00000000 00000000
    test_instruction(0x02c5b533, IN(reg::a1, a), IN(reg::a2, b), RES(reg::a0, 0x200));
}

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