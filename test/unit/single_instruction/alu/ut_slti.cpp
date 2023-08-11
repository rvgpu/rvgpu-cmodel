#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_pseudo_snez_set_to_1) {
    // 0x0085a513 slti a0, a1, 8
    insts.push_back(0x0085a513);

    SetIReg(reg::a1, 6);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), true);

    SetIReg(reg::a1, 10);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), false);
}

TEST_F(ut_inst, decode_and_execute_rv64i_pseudo_snez_set_to_0) {
    // snez: 0xa03533; # snez a0, a0
    insts.push_back(0xa03533);
    auto rega = reg::a0;
    auto regr = reg::a0;

    uint64_t result = 0;
    SetIReg(rega, 0);
    ExecuateInst();
    result = GetIReg(regr);
    EXPECT_EQ(result, 0);
}