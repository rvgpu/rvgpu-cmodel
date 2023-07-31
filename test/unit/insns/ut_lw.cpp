#include <gtest/gtest.h>
#include "sm/compute_unit.h"

#include "ut_insns.hpp"

TEST_F(ut_insns, decode_and_execute_rv64i_lw) {
    // 0x00c92503 : lw a0, 12(s2)
    insts.push_back(0x00c92503);
    
    int32_t *addr = (int32_t *)(GetStackPointer() + 12);
    *addr = 0x10001000;

    auto regr = reg::a0;
    int32_t result = 0;
    SetIReg(reg::s2, GetStackPointer());
    ExecuateInst();
    result = GetIReg(regr);
    EXPECT_EQ(result, 0x10001000);
}