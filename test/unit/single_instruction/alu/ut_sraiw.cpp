#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_slli){
    // 0x4085559b       sraiw    a1, a0, 8
    uint64_t data = 0x8888888888880000;
    test_instruction(0x4085559b, IN(reg::a0, data), RES(reg::a1, ((int32_t)data) >> 8));
}