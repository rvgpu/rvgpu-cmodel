#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64if_fcvt_wu_s) {
    // 0xc0101553       fcvt.wu.s   a0, ft0, rtz
    insts.push_back(0xc0101553);
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a0), 1);
}
