#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64if_fmv_x_w) {
    // 0xe0000553 : fmv.x.w a0, ft0
    insts.push_back(0xe0000553);

    float a = 1.0f;
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(a));

    ExecuateInst();

    uint32_t res = GetIReg(reg::a0);
    EXPECT_EQ(res, 0x3f800000);
}