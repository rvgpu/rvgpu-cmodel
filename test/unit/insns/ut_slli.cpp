#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, should_decode_and_exe_slli_corectly){
    //bits: 0x02061613  #slli a2, a2, 32
    insts.push_back(0x02061613);
    LoadInst();
    WRITE_REG(fetch.insn.rs1(), 0x80000000);
    ExecuateInst();
    auto res = READ_REG(fetch.insn.rd());
    EXPECT_EQ(res, ((uint64_t)0x80000000) << 32);
}