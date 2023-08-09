#include "ut_alu.hpp"

TEST_F(ut_alu, decode_and_execute_rv64im_mul) {
    // 0x02a59633       mulh    a2, a1, a0
    insts.push_back(0x02a59633);
    SetIReg(reg::a1, 0x1000000000);
    SetIReg(reg::a0, 0x2000000000);
    // 0x200 00000000 00000000
    ExecuateInst();
    uint64_t res = GetIReg(reg::a2);
    EXPECT_EQ(res, 0x200);
}