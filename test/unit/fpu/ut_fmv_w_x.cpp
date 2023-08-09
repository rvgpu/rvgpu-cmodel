#include "ut_fpu.hpp"

TEST_F(ut_fpu, decode_and_execute_rv64if_fmv_w_x) {
    // 0xf0000053 : fmv.w.x ft0, zero
    insts.push_back(0xf0000053);

    float a = 1.1f;
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(a));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), 0.0f);
}