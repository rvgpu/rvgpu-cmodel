#include <gtest/gtest.h>
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_or) {
    //bits: 0x00a5e533     #or  a0, a1, a0
    insts.push_back(0x00a5e533);
    LoadInst();

    WRITE_REG(fetch.insn.rs1(), 4);
    WRITE_REG(fetch.insn.rs2(), 1);
    ExecuateInst();
    auto res = READ_REG(fetch.insn.rd());
    EXPECT_EQ(res, 5);
}