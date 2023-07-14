#include <gtest/gtest.h>
#include "sm/compute_unit.h"

#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, shoulde_decode_and_execute_rv64i_lui_correcly) {
    // 0x02000e93 : lui x29, 2
    insts.push_back(0x00002eb7);
    LoadInst();
    ExecuateInst();
    uint64_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(res, 0x2000);
}

TEST_F(ut_rv32_insns, shoulde_decode_and_execute_rv32i_lui_correcly) {
    // 0x02000e93 : lui x29, 2
    insts.push_back(0x00002eb7);
    LoadInst();
    ExecuateInst();
    uint32_t res = READ_REG(fetch.insn.rd());

    EXPECT_EQ(res, 0x2000);
}