#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sw){
    // 0x00a11823       sh  a0, 16(sp)
    insts.push_back(0x00a11823);
    uint32_t * sp = (uint32_t *)GetStackPointer();
    sp[4] = 0xaaaaaaaa;

    SetIReg(reg::a0, 0x1234);
    ExecuateInst();
    EXPECT_EQ(sp[4], 0xaaaa1234);
}