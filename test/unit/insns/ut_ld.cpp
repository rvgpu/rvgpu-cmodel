#include <gtest/gtest.h>
#include "sm/compute_unit.h"

#include "ut_insns.hpp"

TEST_F(ut_insns, decode_and_execute_rv64i_ld) {
    // 0x39813a03 : ld s4, 920(sp)
    insts.push_back(0x39813a03);

    uint64_t *addr = (uint64_t *)(GetStackPointer() + 920);
    *addr = 0x1000100010001000;

    auto regr = reg::s4;
    uint64_t result = 0;
    ExecuateInst();
    result = GetIReg(regr);
    EXPECT_EQ(result, 0x1000100010001000);
}