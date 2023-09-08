#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_slli){
    // 0x43f55593       srai    a1, a0, 63
    test_instruction(0x43f55593, IN(reg::a0, 0x80000000), RES(reg::a1, ((uint64_t)0x80000000) >> 63));
}