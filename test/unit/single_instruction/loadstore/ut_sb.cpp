#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sw){
    // 0x00a58023       sb  a0, 0(a1)
    auto sp = (uint64_t)malloc(32);
    ((uint32_t *)sp)[0] = 0;
    exec_instruction(0x00a58023, IN(reg::a0, 0x12345678), IN(reg::a1, uint64_t(sp)));
    EXPECT_EQ(*(int32_t*)((uint64_t)sp), 0x00000078);
}