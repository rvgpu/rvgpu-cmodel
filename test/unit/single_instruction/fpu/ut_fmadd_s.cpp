#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64if_fmadd_s) {
    // 0x0020f043 : fmadd.s ft0, ft1, ft2, ft0
    insts.push_back(0x0020f043);

    float a = 1.1f;
    float b = 2.1f;
    float c = 3.1f;
    SetFReg(fpreg::ft1, std::bit_cast<uint32_t>(a));
    SetFReg(fpreg::ft2, std::bit_cast<uint32_t>(b));
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(c));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), a * b + c);
}