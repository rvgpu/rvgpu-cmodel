#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#define CHECK_BRANCH(a) do { \
        WRITE_REG(fetch.insn.rs1(), a); \
        ExecuateInst();           \
        auto pc = Getpc();        \
        auto next_pc = GetNextpc(); \
        if (a != 0) { \
            EXPECT_EQ(next_pc, pc - 80); \
        } else { \
            EXPECT_EQ(next_pc, pc + 4); \
        } \
    } while(0)


TEST_F(ut_rv64_insns, decode_and_execute_rv64i_bne) {
    // 0xfa0418e3 : bnez s0, -80 (bne s0, 0, -80)
    insts.push_back(0xfa0418e3);
    LoadInst();

    CHECK_BRANCH(1);
    CHECK_BRANCH(0);
    CHECK_BRANCH(-1);
    CHECK_BRANCH(12);
    CHECK_BRANCH(-12);
}