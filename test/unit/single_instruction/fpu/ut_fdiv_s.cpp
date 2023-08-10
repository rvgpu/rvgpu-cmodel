#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64if_fdiv_s) {
    // 0x1820f0d3 : fdiv.s f1, f1, f2
    insts.push_back(0x1820f0d3);

    float a = 1.1f;
    float b = 2.1f;
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(a));
    SetFReg(fpreg::f2, std::bit_cast<uint32_t>(b));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::f1);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), a / b);
}