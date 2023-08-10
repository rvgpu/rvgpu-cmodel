#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_slli){
    //bits: 0x02061613  #slli a2, a2, 32
    insts.push_back(0x02061613);
    SetIReg(reg::a2, 0x80000000);
    ExecuateInst();

    auto res = GetIReg(reg::a2);
    EXPECT_EQ(res, ((uint64_t)0x80000000) << 32);
}