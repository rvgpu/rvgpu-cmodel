#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sra){
    // 0x40c5d533       sra    a0, a1, a2
    insts.push_back(0x40c5d533);

    SetIReg(reg::a1, 0x87654321000);
    SetIReg(reg::a2, 8);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), ((int64_t)0x87654321000) >> 8);
}