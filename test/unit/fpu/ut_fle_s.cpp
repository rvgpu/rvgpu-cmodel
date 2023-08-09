#include "ut_fpu.hpp"

TEST_F(ut_fpu, decode_and_execute_rv64if_fsub_s) {
    // 0xa0100553  fle.s a0, ft0, ft1
    insts.push_back(0xa0100553);

    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(1.1f));
    SetFReg(fpreg::ft1, std::bit_cast<uint32_t>(2.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);

    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(2.1f));
    SetFReg(fpreg::ft1, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 0);
}