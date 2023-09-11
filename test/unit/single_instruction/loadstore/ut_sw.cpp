#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sw){
    //sw bits: 0x00c52823 # sw  a2, 16(a0)
    auto sp = (uint64_t)malloc(32);
    exec_instruction(0x00c52823, IN(reg::a2, -333), IN(reg::a0, sp));
    EXPECT_EQ(*(int32_t*)((uint64_t)sp + 16), -333);
}