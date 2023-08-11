#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_slli){
    //bits: 0x00c59533  # sll a0, a1, a2
    insts.push_back(0x00c59533);

    SetIReg(reg::a1, 0x88880000);
    SetIReg(reg::a2, 8);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), ((uint64_t)0x88880000) << 8);
}