#include "ut_inst.hpp"

#define CHECK_MUL(sr0, s0, sr1, s1, rd) do { \
        SetIReg(sr0, s0);                    \
        SetIReg(sr1, s1);                    \
        ExecuateInst();                      \
        EXPECT_EQ(GetIReg(rd), (s0 * s1));   \
    } while(0)

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