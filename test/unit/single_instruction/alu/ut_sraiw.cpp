#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_slli){
    // 0x4085559b       sraiw    a1, a0, 8
    insts.push_back(0x4085559b);

    uint64_t data = 0x8888888888880000;
    SetIReg(reg::a0, data);
    ExecuateInst();
    EXPECT_EQ(GetIReg(reg::a1), ((int32_t)data) >> 8);
}