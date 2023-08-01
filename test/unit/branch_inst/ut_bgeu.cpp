#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_branch.hpp"

#define CHECK_BRANCH(a, b) do {         \
        SetIReg(rs1, a);                \
        SetIReg(rs2, b);                \
        ExecuateInst();                 \
        auto next_pc = GetPC();         \
        if (a >= b) { \
            EXPECT_EQ(next_pc, pc + 76); \
        } else { \
            EXPECT_EQ(next_pc, pc + 4); \
        } \
    } while(0)


TEST_F(ut_branch, decode_and_execute_rv64i_bgeu) {
    // 0x0496f663 : bgeu a3, s1, 76
    insts.push_back(0x0496f663);
    reg rs1 = reg::a3;
    reg rs2 = reg::s1;
    auto pc = (uint64_t)insts.data();

    CHECK_BRANCH(1, 2);
    CHECK_BRANCH(2, 2);
    CHECK_BRANCH(3, 2);
    CHECK_BRANCH(2, 0);
    CHECK_BRANCH(0, 2);
    CHECK_BRANCH(0, 0);
}