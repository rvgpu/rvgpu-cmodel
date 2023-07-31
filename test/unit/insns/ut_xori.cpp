#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_insns, decode_and_execute_rv64i_xori) {
    // 0x001aca93 : xori s5, s5, 1
    insts.push_back(0x001aca93);
    SetIReg(reg::s5, 7);
    ExecuateInst();
    auto res = GetIReg(reg::s5);

    EXPECT_EQ(res, 6);
}