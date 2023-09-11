#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fmul_d) {
    // 0x12b6f6d3 : fmul.d fa3, fa3, fa1
    insts.push_back(0x12b6f6d3);

    double a = 1.1f;
    double b = 2.1f;
    SetFReg(fpreg::fa3, std::bit_cast<uint64_t>(a));
    SetFReg(fpreg::fa1, std::bit_cast<uint64_t>(b));

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::fa3);
    EXPECT_DOUBLE_EQ(std::bit_cast<double>(res), a * b);
}

TEST_F(ut_inst, decode_and_execute_rv64if_fmul_s) {
    // 0x10b6f6d3 : fmul.s fa3, fa3, fa1
    insts.push_back(0x10b6f6d3);

    float a = 1.1f;
    float b = 2.1f;
    SetFReg(fpreg::fa3, std::bit_cast<uint32_t>(a));
    SetFReg(fpreg::fa1, std::bit_cast<uint32_t>(b));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::fa3);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), a * b);
}