#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_pseudo_j) {
    // 0x0380006f : j 56 (jal x0, 56)
    insts.push_back(0x0380006f);
    LoadInst();
    ExecuateInst();
    auto pc = Getpc();
    auto next_pc = GetNextpc();

    EXPECT_EQ(next_pc, pc + 56);
}