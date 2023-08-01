#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_alu.hpp"

TEST_F(ut_alu, decode_and_execute_rv64i_ori) {
    //bits: 0x0044e513     #ori a0, s1, 4
    insts.push_back(0x0044e513);
    SetIReg(reg::s1, 1);

    ExecuateInst();

    auto res = GetIReg(reg::a0);
    EXPECT_EQ(res, 5);
}