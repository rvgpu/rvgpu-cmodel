#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_xori) {
    // 0x00c5c533 xor a0, a1, a2
    insts.push_back(0x00c5c533);

    SetIReg(reg::a1, 0x88880000);
    SetIReg(reg::a2, 0x87654321);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), uint64_t(0x88880000) ^ uint64_t(0x87654321));
}