#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_andi) {
    // 0x020bfb93 : andi s7, s7, 32
    insts.push_back(0x020bfb93);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 33);
    ExecuateInst();
    auto res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(res, 32);
}