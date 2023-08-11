#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64im_mul) {
    // 0x02c5a533       mulhsu    a0, a1, a2
    insts.push_back(0x02c5a533);

    SetIReg(reg::a1, 0x1000000000);
    SetIReg(reg::a2, 0x2000000000);
    // 0x200 00000000 00000000
    ExecuateInst();
    uint64_t res = GetIReg(reg::a0);
    EXPECT_EQ(res, 0x200);
}