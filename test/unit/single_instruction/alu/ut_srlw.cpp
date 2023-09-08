#include "ut_inst.hpp"

static inline uint64_t sllw(uint64_t a, uint64_t b)
{
    uint64_t res = int32_t((uint32_t)a >> (b & 0x1F));
    return res;
}

TEST_F(ut_inst, decode_and_execute_rv64i_sllw){
    // 0x00c5d53b       srli    a0, a1, a2
    uint64_t a = 0x87654321000;
    uint64_t b = 0x8;
    test_instruction(0x00c5d53b, IN(reg::a1, a), IN(reg::a2, b), RES(reg::a0, int32_t((uint32_t)a >> (b & 0x1F))));
}