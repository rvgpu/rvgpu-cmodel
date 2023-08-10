#include "ut_inst.hpp"

#define CHECK_MUL(sr0, s0, sr1, s1, rd) do { \
        SetIReg(sr0, s0);                    \
        SetIReg(sr1, s1);                    \
        ExecuateInst();                      \
        EXPECT_EQ(GetIReg(rd), (s0 * s1));   \
    } while(0)

TEST_F(ut_inst, decode_and_execute_rv64im_mulw) {
    // 0x03da8c3b : mulw s8, s5, t4
    insts.push_back(0x03da8c3b);
    CHECK_MUL(reg::s5, 2, reg::t4, 1, reg::s8);
    CHECK_MUL(reg::s5, 1, reg::t4, 2, reg::s8);
    CHECK_MUL(reg::s5, -11, reg::t4, 12, reg::s8);
    CHECK_MUL(reg::s5, 11, reg::t4, -12, reg::s8);
    CHECK_MUL(reg::s5, -11, reg::t4, -12, reg::s8);
}