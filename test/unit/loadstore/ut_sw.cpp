#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sw){
    //sw bits: 0x00c52823 # sw  a2, 16(a0)
    insts.push_back(0x00c52823);

    auto sp = (uint64_t)malloc(32);
    SetIReg(reg::a0, sp);
    SetIReg(reg::a2, -333);
    ExecuateInst();
    EXPECT_EQ(*(int32_t*)((uint64_t)sp + 16), -333);
}