#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fmv_d_x) {
    // 0xf2000053 : fmv.d.x ft0, zero
    insts.push_back(0xf2000053);

    double a = 1.1;
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(a));

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft0);
    EXPECT_DOUBLE_EQ(std::bit_cast<double>(res), 0.0);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fmv_w_x) {
    // 0xf0000053 : fmv.w.x ft0, zero
    insts.push_back(0xf0000053);

    float a = 1.1f;
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(a));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), 0.0f);
}

TEST_F(ut_inst, decode_and_execute_rv64id_fmv_x_d) {
    // 0xe2000553 : fmv.x.d a0, ft0
    insts.push_back(0xe2000553);

    double a = 1.0;
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(a));

    ExecuateInst();

    uint64_t res = GetIReg(reg::a0);
    EXPECT_EQ(res, 0x3ff0000000000000);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fmv_x_w) {
    // 0xe0000553 : fmv.x.w a0, ft0
    insts.push_back(0xe0000553);

    float a = 1.0f;
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(a));

    ExecuateInst();

    uint32_t res = GetIReg(reg::a0);
    EXPECT_EQ(res, 0x3f800000);
}