#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_l) {
    // 0xd2257053 fcvt.d.l   ft0, a0
    insts.push_back(0xd2257053);

    SetIReg(reg::a0, 1);

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft0);
    EXPECT_EQ(res, 0x3ff0000000000000);
}
