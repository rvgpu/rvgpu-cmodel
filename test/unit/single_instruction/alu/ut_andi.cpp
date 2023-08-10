#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_andi) {
    // 0x020bfb93 : andi s7, s7, 32
    insts.push_back(0x020bfb93);
    SetIReg(reg::s7, 33);
    ExecuateInst();
    auto res = GetIReg(reg::s7);

    EXPECT_EQ(res, 32);
}