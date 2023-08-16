#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fmv_x_d) {
    // 0xe2000553 : fmv.x.d a0, ft0
    insts.push_back(0xe2000553);

    double a = 1.0;
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(a));

    ExecuateInst();

    uint64_t res = GetIReg(reg::a0);
    EXPECT_EQ(res, 0x3ff0000000000000);
}