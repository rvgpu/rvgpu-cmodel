#include <gtest/gtest.h>
#include "ut_alu.hpp"

#define CHECK_MUL(sr0, s0, sr1, s1, rd) do { \
        SetIReg(sr0, s0);                    \
        SetIReg(sr1, s1);                    \
        ExecuateInst();                      \
        EXPECT_EQ(GetIReg(rd), (s0 * s1));   \
    } while(0)

TEST_F(ut_alu, decode_and_execute_rv64im_mul) {
    // 0x02b50533 : mul	a0, a0, a1
    insts.push_back(0x02b50533);
    CHECK_MUL(reg::a0, 2, reg::a1, 1, reg::a0);
    CHECK_MUL(reg::a0, 1, reg::a1, 2, reg::a0);
    CHECK_MUL(reg::a0, -11, reg::a1, 12, reg::a0);
    CHECK_MUL(reg::a0, 11, reg::a1, -12, reg::a0);
    CHECK_MUL(reg::a0, -11, reg::a1, -12, reg::a0);
}