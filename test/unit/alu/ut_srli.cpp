#include "ut_alu.hpp"

TEST_F(ut_alu, decode_and_execute_rv64i_slli){
    // 0x03f55593       srli    a1, a0, 63
    insts.push_back(0x03f55593);
    SetIReg(reg::a0, 0x80000000);
    ExecuateInst();

    auto res = GetIReg(reg::a1);
    EXPECT_EQ(res, ((uint64_t)0x80000000) >> 63);
}