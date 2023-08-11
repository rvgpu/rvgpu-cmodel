#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_slli){
    // 0x0085d51b         srliw   a0, a1, 8
    insts.push_back(0x0085d51b);

    SetIReg(reg::a1, 0x8888888888880000);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 0x0000000000888800);
}