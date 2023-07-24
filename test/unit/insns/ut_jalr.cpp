#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_pseudo_ret) {
    // 0x00008067 : ret (jalr x0, x1, 0)
    insts.push_back(0x8067);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 0x1111);
    ExecuateInst();
    auto next_pc = GetNextpc();

    EXPECT_EQ(next_pc, 0x1110);
}

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_pseudo_jalr) {
    // 0x000080e7 : jalr ra (jalr x1, ra, 0)
    insts.push_back(0x80e7);
    uint64_t result;
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 0x1111);
    ExecuateInst();
    auto pc = Getpc();
    auto next_pc = GetNextpc();
    result = READ_REG(fetch.insn.rd());

    EXPECT_EQ(next_pc, 0x1110);
    EXPECT_EQ(result, pc + 4);
}