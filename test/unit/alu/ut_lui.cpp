#include "ut_alu.hpp"

TEST_F(ut_alu, decode_and_execute_rv64i_lui) {
    // 0x02000e93 : lui x29, 2
    insts.push_back(0x00002eb7);    
    auto regr = reg::x29;

    uint64_t result = 0;
    ExecuateInst();
    result = GetIReg(regr);
    EXPECT_EQ(result, 0x2000);
}