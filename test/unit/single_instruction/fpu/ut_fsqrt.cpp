#include "ut_inst.hpp"
#include <math.h>

TEST_F(ut_inst, decode_and_execute_rv64id_fsqrt_d) {
    // 0x5a00f053 : fsqrt.s f0, f1
    insts.push_back(0x5a00f053);

    double a = 1.1f;
    SetFReg(fpreg::f1, std::bit_cast<uint64_t>(a));

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::f0);
    EXPECT_DOUBLE_EQ(std::bit_cast<double>(res), sqrt(a));
}

TEST_F(ut_inst, decode_and_execute_rv64if_fsqrt_s) {
    // 0x5800f053 : fsqrt.s f0, f1
    insts.push_back(0x5800f053);

    float a = 1.1f;
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(a));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), sqrt(a));
}