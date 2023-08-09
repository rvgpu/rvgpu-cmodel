#include "ut_fpu.hpp"

TEST_F(ut_fpu, decode_and_execute_rv64if_fcvt_s_wu) {
    // 0xc0301553       fcvt.lu.s   a0, ft0, rtz
    insts.push_back(0xc0301553);
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);
}
