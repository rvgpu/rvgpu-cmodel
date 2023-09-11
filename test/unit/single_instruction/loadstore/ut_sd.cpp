#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sd) {
    //bits: 0x00a13c23   sd  a0, 24(sp)
    exec_instruction(0x00a13c23, IN(reg::a0, 0x1000100010001000), IN(reg::sp, GetStackPointer()));
    EXPECT_EQ(*(int64_t*)((uint64_t)GetStackPointer() + 24), 0x1000100010001000);
}