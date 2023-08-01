#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_alu.hpp"

#define CHECK_ADD(a, b) do {                    \
        uint64_t result = 0;                    \
        SetIReg(rega, a);                       \
        SetIReg(regb, b);                       \
        ExecuateInst();                         \
        result = GetIReg(regr);                 \
        EXPECT_EQ(result, (a + b));             \
    } while(0)

TEST_F(ut_alu, decode_and_execute_rv64i_addw) {
    // 0x00e5053b : addw a0, a0, a4
    insts.push_back(0x00e5053b);    
    auto rega = reg::a0;
    auto regb = reg::a4;
    auto regr = reg::a0;

    CHECK_ADD(11, 12);
    CHECK_ADD(-11, 12);
    CHECK_ADD(11, -12);
    CHECK_ADD(11, 0);
    CHECK_ADD(0, 12);
}