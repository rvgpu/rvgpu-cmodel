#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_s_d) {
    // 0x4010f053       fcvt.s.d   f0, f1
    insts.push_back(0x4010f053);
    SetFReg(fpreg::f1, std::bit_cast<uint64_t>(1.1));
    ExecuateInst();
    
    uint32_t res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), 1.1f);
}
