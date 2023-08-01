#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_branch.hpp"

TEST_F(ut_branch, decode_and_execute_rv64i_pseudo_ret) {
    // 0x00008067 : ret (jalr x0, x1, 0)
    insts.push_back(0x8067);
    SetIReg(reg::x1, 0x1111);

    ExecuateInst();
    auto next_pc = GetPC();

    EXPECT_EQ(next_pc, 0x1110);
}

TEST_F(ut_branch, decode_and_execute_rv64i_pseudo_jalr) {
    // 0x000080e7 : jalr ra (jalr x1, ra, 0)
    insts.push_back(0x80e7);
    SetIReg(reg::ra, 0x1111);
    ExecuateInst();

    auto pc = (uint64_t)insts.data();
    auto npc = GetPC();
    auto res = GetIReg(reg::x1);
    EXPECT_EQ(npc, 0x1110);
    EXPECT_EQ(res, pc + 4);
}
