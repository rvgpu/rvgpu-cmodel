#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sll){
    //bits: 0x00c59533  # sll a0, a1, a2
    test_instruction(0x00c59533, IN(reg::a1, 0x88880000), IN(reg::a2, 8), RES(reg::a0, ((uint64_t)0x88880000) << 8));
}

TEST_F(ut_inst, decode_and_execute_rv64i_slli) {
    //bits: 0x02061613  #slli a2, a2, 32
    test_instruction(0x02061613, IN(reg::a2, 0x88880000), RES(reg::a2, ((uint64_t)0x88880000) << 32));
}

TEST_F(ut_inst, decode_and_execute_rv64i_slliw) {
    //bits 0x00169c1b  #slliw   s8, a3, 1
    //operate on 32-bit values and produce signed 32-bit results
    test_instruction(0x00169c1b, IN(reg::a3, 0xf0000001), RES(reg::s8, (int64_t)(int32_t)(0xf0000001 << 1)));
}

static inline uint64_t sllw(uint64_t a, uint64_t b)
{
    uint64_t res = uint64_t(int32_t(a << (b & 0x1F)));
    return res;
}

TEST_F(ut_inst, decode_and_execute_rv64i_sllw) {
    // 0x00c5953b sllw a0, a1, a2
    uint64_t a = 0x87654321000;
    uint64_t b = 8;
    test_instruction(0x00c5953b, IN(reg::a1, a), IN(reg::a2, b), RES(reg::a0, uint64_t(int32_t(a << (b & 0x1F)))));
}