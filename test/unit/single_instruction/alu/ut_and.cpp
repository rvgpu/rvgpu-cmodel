#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_andi) {
    // 0x00c5f533 : and a0, a1, a2
    insts.push_back(0x00c5f533);

    uint64_t a = 0xff876543210;
    uint64_t b = 0x123456780ff;
    SetIReg(reg::a1, a);
    SetIReg(reg::a2, b);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), a & b);
}