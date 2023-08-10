#include "ut_inst.hpp"

#define CHECK_BRANCH(a) do {        \
        SetIReg(rs1, a);            \
        ExecuateInst();             \
        auto next_pc = GetPC();     \
        if (a != 0) {               \
            EXPECT_EQ(next_pc, pc - 80); \
        } else { \
            EXPECT_EQ(next_pc, pc + 4); \
        } \
    } while(0)


TEST_F(ut_inst, decode_and_execute_rv64i_bne) {
    // 0xfa0418e3 : bnez s0, -80 (bne s0, x0, -80)
    insts.push_back(0xfa0418e3);
    reg rs1 = reg::s0;
    auto pc = (uint64_t)insts.data();

    CHECK_BRANCH(1);
    CHECK_BRANCH(0);
    CHECK_BRANCH(-1);
    CHECK_BRANCH(12);
    CHECK_BRANCH(-12);
}