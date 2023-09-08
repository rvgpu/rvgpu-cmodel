#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_slli){
    // 0x0085d51b         srliw   a0, a1, 8
    uint64_t a = 0x8888888888880000;
    test_instruction(0x0085d51b, IN(reg::a1, a), RES(reg::a0, 0x0000000000888800));
}