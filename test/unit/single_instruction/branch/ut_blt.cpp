#include "ut_inst.hpp"

#define CHECK_BRANCH(rs1, s1, rs2, s2) do { \
        SetIReg(rs1, s1);                   \
        SetIReg(rs2, s2);                   \
        ExecuateInst();                     \
        if (s1 < s2) {                      \
            EXPECT_EQ(GetPC(), pc + 16);     \
        } else {                            \
            EXPECT_EQ(GetPC(), pc + 4);     \
        }                                   \
    } while(0)


TEST_F(ut_inst, decode_and_execute_rv64i_bltu) {
    // 0x00b54864 : blt a0, a1, 16
    insts.push_back(0x00b54863);
    uint64_t pc = (uint64_t)insts.data();

    CHECK_BRANCH(reg::a0, 1, reg::a1, 2);
    CHECK_BRANCH(reg::a0, 2, reg::a1, 2);
    CHECK_BRANCH(reg::a0, 3, reg::a1, 2);
    CHECK_BRANCH(reg::a0, 2, reg::a1, 0);
    CHECK_BRANCH(reg::a0, 0, reg::a1, 2);
    CHECK_BRANCH(reg::a0, 0, reg::a1, 0);
}