#include "ut_fpu.hpp"

TEST_F(ut_fpu, decode_and_execute_rv64if_fcvt_s_wu) {
    // 0xd0157053 fcvt.s.wu   ft0, a0
    insts.push_back(0xd0157053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft0);
    printf("%x\n", res);
    EXPECT_EQ(res, 0x3f800000);
}
