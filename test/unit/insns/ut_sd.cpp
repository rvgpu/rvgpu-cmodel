#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_sd) {
    //bits: 0x00a13c23   sd  a0, 24(sp)
    insts.push_back(0x00a13c23);
    LoadInst();
    WRITE_REG(fetch.insn.rs2(), 0x1000100010001000);
    WRITE_REG(fetch.insn.rs1(), (uint64_t)sp);

    ExecuateInst();

    EXPECT_EQ(*(uint64_t*)((uint64_t)sp + 24), 0x1000100010001000);
}