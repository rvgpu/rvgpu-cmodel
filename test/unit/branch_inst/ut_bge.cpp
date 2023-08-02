#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_branch.hpp"

#define CHECK_BRANCH(a, b) do {         \
        SetIReg(rs1, a);                \
        SetIReg(rs2, b);                \
        ExecuateInst();                 \
        auto next_pc = GetPC();         \
        if (int64_t(a) >= int64_t(b)) { \
            EXPECT_EQ(next_pc, pc + 44); \
        } else {                        \
            EXPECT_EQ(next_pc, pc + 4); \
        } \
    } while(0)


TEST_F(ut_branch, decode_and_execute_rv64i_bgeu) {
    // 63 56 b5 02   bge a0, a1, 44
    insts.push_back(0x02b55663);
    reg rs1 = reg::a0;
    reg rs2 = reg::a1;
    auto pc = (uint64_t)insts.data();

    CHECK_BRANCH(1, 2);
    CHECK_BRANCH(1, -2);
    CHECK_BRANCH(2, 1);
    CHECK_BRANCH(2, -1);
    CHECK_BRANCH(-1, 2);
    CHECK_BRANCH(-1, -2);
    CHECK_BRANCH(-2, 1);
    CHECK_BRANCH(-2, -1);
}
