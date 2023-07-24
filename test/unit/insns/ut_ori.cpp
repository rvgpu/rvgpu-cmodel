#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_ori) {
    //bits: 0x0044e513     #ori a0, s1, 4
    insts.push_back(0x0044e513);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 1);

    ExecuateInst();

    auto res = READ_REG(fetch.insn.rd());
    EXPECT_EQ(res, 5);
}