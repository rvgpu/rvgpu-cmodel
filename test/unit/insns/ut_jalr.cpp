#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_ret) {
    //bit :0x00008067    #ret    eq to : jalr x0, 0(x1)
    insts.push_back(0x8067);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 0x1111);
    ExecuateInst();
    auto next_pc = GetNextpc();

    EXPECT_EQ(next_pc, 0x1110);
}