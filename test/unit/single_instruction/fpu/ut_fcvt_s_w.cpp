#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_s_w) {
    // 0xd0057053 fcvt.s.w   ft0, a0
    insts.push_back(0xd0057053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft0);
    EXPECT_EQ(res, 0x3f800000);
}
