#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_srl){
    // 0x00c5d533       srl    a0, a1, a2
    uint64_t data = 0x87654321000;
    test_instruction(0x00c5d533, IN(reg::a1, data), IN(reg::a2, 8), RES(reg::a0, 0x87654321000 >> 8));
}

TEST_F(ut_inst, decode_and_execute_rv64i_srli){
    // 0x03f55593       srli    a1, a0, 63
    test_instruction(0x03f55593, IN(reg::a0, 0x80000000), RES(reg::a1, ((uint64_t)0x80000000) >> 63));
}

TEST_F(ut_inst, decode_and_execute_rv64i_srliw){
    // 0x0085d51b         srliw   a0, a1, 8
    uint64_t a = 0x8888888888880000;
    test_instruction(0x0085d51b, IN(reg::a1, a), RES(reg::a0, 0x0000000000888800));
}

TEST_F(ut_inst, decode_and_execute_rv64i_srlw){
    // 0x00c5d53b       srlw    a0, a1, a2
    uint64_t a = 0x87654321000;
    uint64_t b = 0x8;
    test_instruction(0x00c5d53b, IN(reg::a1, a), IN(reg::a2, b), RES(reg::a0, int32_t((uint32_t)a >> (b & 0x1F))));
}