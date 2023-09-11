#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fsub_d) {
    // 0x0a107053   fsub.d	ft0, ft0, ft1
    insts.push_back(0x0a107053);

    double a = 1.1f;
    double b = 2.1f;
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(a));
    SetFReg(fpreg::ft1, std::bit_cast<uint64_t>(b));

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft0);
    EXPECT_DOUBLE_EQ(std::bit_cast<double>(res), a - b);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fsub_s) {
    // 0x08107053   fsub.s	ft0, ft0, ft1
    insts.push_back(0x08107053);

    float a = 1.1f;
    float b = 2.1f;
    SetFReg(fpreg::f0, std::bit_cast<uint32_t>(a));
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(b));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), a - b);
}