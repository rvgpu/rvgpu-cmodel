#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fnmadd_d) {
    // 0x0220f04f : fnmadd.d ft0, ft1, ft2, ft0
    insts.push_back(0x0220f04f);

    double a = 1.1f;
    double b = 2.1f;
    double c = 3.1f;
    SetFReg(fpreg::ft1, std::bit_cast<uint64_t>(a));
    SetFReg(fpreg::ft2, std::bit_cast<uint64_t>(b));
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(c));

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft0);
    EXPECT_DOUBLE_EQ(std::bit_cast<double>(res), -(a * b + c));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fnmadd_s) {
    // 0x0020f04f : fnmadd.s ft0, ft1, ft2, ft0
    insts.push_back(0x0020f04f);

    float a = 1.1f;
    float b = 2.1f;
    float c = 3.1f;
    SetFReg(fpreg::ft1, std::bit_cast<uint32_t>(a));
    SetFReg(fpreg::ft2, std::bit_cast<uint32_t>(b));
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(c));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), -(a * b + c));
}