#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_xori) {
    // 0x001aca93 : xori s5, s5, 1
    insts.push_back(0x001aca93);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 7);
    ExecuateInst();
    auto res = READ_REG(fetch.insn.rd());
    
    EXPECT_EQ(res, 6);
}