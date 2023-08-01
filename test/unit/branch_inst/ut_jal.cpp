#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_branch.hpp"

TEST_F(ut_branch, decode_and_execute_rv64i_pseudo_j) {
    // 0x0380006f : j 56 (jal x0, 56)
    insts.push_back(0x0380006f);

    ExecuateInst();

    auto pc = (uint64_t)insts.data();
    auto next_pc = GetPC();

    EXPECT_EQ(next_pc, pc + 56);
}