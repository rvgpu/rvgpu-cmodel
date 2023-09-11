#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fnmsub_d) {
    // 0x2210724b   fnmsub.d ft4, ft0, ft1, ft4
    insts.push_back(0x2210724b);

    double a = 1.1f;
    double b = 2.1f;
    double c = 3.3f;
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(a));
    SetFReg(fpreg::ft1, std::bit_cast<uint64_t>(b));
    SetFReg(fpreg::ft4, std::bit_cast<uint64_t>(c));

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft4);
    EXPECT_DOUBLE_EQ(std::bit_cast<double>(res), -(a * b - c));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fnmsub_s) {
    // 0x2010724b   fnmsub.s ft4, ft0, ft1, ft4
    insts.push_back(0x2010724b);

    float a = 1.1f;
    float b = 2.1f;
    float c = 3.1f;
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(a));
    SetFReg(fpreg::ft1, std::bit_cast<uint32_t>(b));
    SetFReg(fpreg::ft4, std::bit_cast<uint32_t>(c));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::ft4);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), -(a * b - c));
}
