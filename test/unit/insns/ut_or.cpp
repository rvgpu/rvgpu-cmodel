#include <gtest/gtest.h>
#include "ut_insns.hpp"

TEST_F(ut_insns, decode_and_execute_rv64i_or) {
    //bits: 0x00a5e533     #or  a0, a1, a0
    insts.push_back(0x00a5e533);
    SetIReg(reg::a1, 4);
    SetIReg(reg::a0, 1);

    ExecuateInst();
    auto res = GetIReg(reg::a0);

    EXPECT_EQ(res, 5);
}