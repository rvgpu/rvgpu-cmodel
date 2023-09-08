#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_srl){
    // 0x00c5d533       srl    a0, a1, a2
    uint64_t data = 0x87654321000;
    test_instruction(0x00c5d533, IN(reg::a1, data), IN(reg::a2, 8), RES(reg::a0, 0x87654321000 >> 8));
}