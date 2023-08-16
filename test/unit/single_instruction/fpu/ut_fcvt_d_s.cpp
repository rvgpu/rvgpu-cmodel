#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fcvt_d_s) {
    // 0x4200f053       fcvt.d.s   f0, f1
    insts.push_back(0x4200f053);
    SetFReg(fpreg::f1, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    
    uint64_t res = GetFReg(fpreg::f0);
    EXPECT_FLOAT_EQ(std::bit_cast<double>(res), 1.1);
}
