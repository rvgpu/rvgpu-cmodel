#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#define CHECK_ADD(a, b) do {                    \
        uint64_t result = 0;                    \
        SetIReg(rega, a);                       \
        SetIReg(regb, b);                       \
        ExecuateInst();                         \
        result = GetIReg(regr);                 \
        EXPECT_EQ(result, (a + b));             \
    } while(0)

TEST_F(ut_insns, decode_and_execute_rv64i_add) {
    //0x00d786b3 : add a3, a5, a3
    insts.push_back(0x00d786b3);
    uint32_t rega = REG_a5;
    uint32_t regb = REG_a3;
    uint32_t regr = REG_a3;

    CHECK_ADD(1, 2);
}