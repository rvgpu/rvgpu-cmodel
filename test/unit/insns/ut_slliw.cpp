#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, should_decode_and_exe_swlli_corectly) {
    //bits 0x00169c1b  #slliw   s8, a3, 1
    //operate on 32-bit values and produce signed 32-bit results
    insts.push_back(0x00169c1b);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(),0xf0000001);
    ExecuateInst();
    auto result = READ_REG(fetch.insn.rd());
    EXPECT_EQ(result, (int64_t)(int32_t)(0xf0000001 << 1));
}