#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sra){
    // 0x40c5d53b       sraw    a0, a1, a2
    uint64_t a = 0x87654321000;
    uint64_t b = 0x8;
    test_instruction(0x40c5d53b, IN(reg::a1, a), IN(reg::a2, b), RES(reg::a0, int32_t(int32_t(a) >> (b & 0x1F))));
}