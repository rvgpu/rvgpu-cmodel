#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_srl){
    // 0x00c5d533       srl    a0, a1, a2
    insts.push_back(0x00c5d533);

    SetIReg(reg::a1, 0x87654321000);
    SetIReg(reg::a2, 8);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 0x87654321000 >> 8);
}