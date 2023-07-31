#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_insns, decode_and_execute_rv64i_sd) {
    //bits: 0x00a13c23   sd  a0, 24(sp)
    insts.push_back(0x00a13c23);
    SetIReg(reg::a0, 0x1000100010001000);

    ExecuateInst();
    EXPECT_EQ(*(int64_t*)((uint64_t)GetIReg(reg::sp) + 24), 0x1000100010001000);
}