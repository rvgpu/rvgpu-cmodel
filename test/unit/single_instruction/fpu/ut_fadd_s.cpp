#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64if_fadd_s) {
    // 0x00107053 : fadd.s f0, f0, f1
    insts.push_back(0x00107053);

    float a = 1.1f;
    float b = 2.1f;
    SetFReg(fpreg::f0, std::bit_cast<uint32_t>(a));
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(b));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), a + b);
}