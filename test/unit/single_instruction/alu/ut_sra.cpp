#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sra){
    // 0x40c5d533       sra    a0, a1, a2
    uint64_t a = 0x87654321000;
    test_instruction(0x40c5d533, IN(reg::a1, a), IN(reg::a2, 8), RES(reg::a0, (((int64_t)0x87654321000) >> 8)));
}

TEST_F(ut_inst, decode_and_execute_rv64i_srai){
    // 0x43f55593       srai    a1, a0, 63
    test_instruction(0x43f55593, IN(reg::a0, 0x80000000), RES(reg::a1, ((uint64_t)0x80000000) >> 63));
}

TEST_F(ut_inst, decode_and_execute_rv64i_sraiw){
    // 0x4085559b       sraiw    a1, a0, 8
    uint64_t data = 0x8888888888880000;
    test_instruction(0x4085559b, IN(reg::a0, data), RES(reg::a1, ((int32_t)data) >> 8));
}

TEST_F(ut_inst, decode_and_execute_rv64i_sraw){
    // 0x40c5d53b       sraw    a0, a1, a2
    uint64_t a = 0x87654321000;
    uint64_t b = 0x8;
    test_instruction(0x40c5d53b, IN(reg::a1, a), IN(reg::a2, b), RES(reg::a0, int32_t(int32_t(a) >> (b & 0x1F))));
}
