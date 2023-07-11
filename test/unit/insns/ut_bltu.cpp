#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#define CHECK_BRANCH(a, b) do { \
        WRITE_REG(fetch.insn.rs1(), a); \
        WRITE_REG(fetch.insn.rs2(), b); \
        ExecuateInst();           \
        auto pc = Getpc();        \
        auto next_pc = GetNextpc(); \
        if (a < b) { \
            EXPECT_EQ(next_pc, pc + 8); \
        } else { \
            EXPECT_EQ(next_pc, pc + 4); \
        } \
    } while(0)


TEST_F(ut_rv64_insns, should_decode_and_execute_rv64i_add_correctly) {
    // 0x009ce463 : bltu s9, s1, 8
    insts.push_back(0x009ce463);
    LoadInst();
    
    CHECK_BRANCH(1, 2);
    CHECK_BRANCH(2, 2);
    CHECK_BRANCH(3, 2);
    CHECK_BRANCH(2, 0);
    CHECK_BRANCH(0, 2);
    CHECK_BRANCH(0, 0);
}