#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sra){
    // 0x40c5d533       sra    a0, a1, a2
    uint64_t a = 0x87654321000;
    test_instruction(0x40c5d533, IN(reg::a1, a), IN(reg::a2, 8), RES(reg::a0, (((int64_t)0x87654321000) >> 8)));
}