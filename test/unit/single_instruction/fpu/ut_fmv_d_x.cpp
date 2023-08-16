#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fmv_d_x) {
    // 0xf2000053 : fmv.d.x ft0, zero
    insts.push_back(0xf2000053);

    double a = 1.1;
    SetFReg(fpreg::ft0, std::bit_cast<uint64_t>(a));

    ExecuateInst();

    uint64_t res = GetFReg(fpreg::ft0);
    EXPECT_DOUBLE_EQ(std::bit_cast<double>(res), 0.0);
}