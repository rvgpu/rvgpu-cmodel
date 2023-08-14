#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fdiv_d) {
    // 0x1a20f0d3 : fdiv.d f1, f1, f2
    insts.push_back(0x1a20f0d3);

    double a = 1.1f;
    double b = 2.1f;
    SetFReg(fpreg::f1, std::bit_cast<uint64_t>(a));
    SetFReg(fpreg::f2, std::bit_cast<uint64_t>(b));

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::f1);
    EXPECT_DOUBLE_EQ(std::bit_cast<double>(res), a / b);
}