#include "ut_fpu.hpp"

TEST_F(ut_fpu, decode_and_execute_rv64if_fmadd_s) {
    // 0x20107247   fmsub.s ft4, ft0, ft1, ft4
    insts.push_back(0x20107247);

    float a = 1.1f;
    float b = 2.1f;
    float c = 3.1f;
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(a));
    SetFReg(fpreg::ft1, std::bit_cast<uint32_t>(b));
    SetFReg(fpreg::ft4, std::bit_cast<uint32_t>(c));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft4);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), a * b - c);
}
