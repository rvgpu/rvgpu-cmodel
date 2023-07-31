#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#define CHECK_BRANCH(rs1, s1, rs2, s2) do { \
        SetIReg(rs1, s1);                   \
        SetIReg(rs2, s2);                   \
        ExecuateInst();                     \
        if (s1 < s2) {                      \
            EXPECT_EQ(GetPC(), pc + 8);     \
        } else {                            \
            EXPECT_EQ(GetPC(), pc + 4);     \
        }                                   \
    } while(0)


TEST_F(ut_insns, decode_and_execute_rv64i_bltu) {
    // 0x009ce463 : bltu s9, s1, 8
    insts.push_back(0x009ce463);
    uint64_t pc = (uint64_t)insts.data();

    CHECK_BRANCH(reg::s9, 1, reg::s1, 2);
    CHECK_BRANCH(reg::s9, 2, reg::s1, 2);
    CHECK_BRANCH(reg::s9, 3, reg::s1, 2);
    CHECK_BRANCH(reg::s9, 2, reg::s1, 0);
    CHECK_BRANCH(reg::s9, 0, reg::s1, 2);
    CHECK_BRANCH(reg::s9, 0, reg::s1, 0);
}