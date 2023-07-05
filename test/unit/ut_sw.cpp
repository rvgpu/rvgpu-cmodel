#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_insns, should_decode_and_execute_sw_correctly) {
    //sw bits: 0x48112623
    insts.push_back(0x48112623);
    uint32_t sp_low = (uint64_t)sp & 0xffffffff;
    LoadInst();

    WRITE_REG(fetch.insn.rs1(), sp_low);
    WRITE_REG(fetch.insn.rs2(), 333);

    ExecuateInst();
    EXPECT_EQ(*(uint32_t*)((uint64_t)sp + 1164), 333);
}