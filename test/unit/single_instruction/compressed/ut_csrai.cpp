#include "ut_compressed.hpp"

TEST_F(ut_compressed, decode_and_execuate_c_srai) {
    uint32_t data = 0x1234;
    check_one_src(0x8505, make_pair(reg::a0, data), make_pair(reg::a0, data >> 1)); // 0x8505: c.srai a0, 1 ==> srli a0, a0, 1
    check_one_src(0x8509, make_pair(reg::a0, data), make_pair(reg::a0, data >> 2)); // 0x8509: c.srai a0, 2 ==> srli a0, a0, 2
    check_one_src(0x850d, make_pair(reg::a0, data), make_pair(reg::a0, data >> 3)); // 0x850d: c.srai a0, 3 ==> srli a0, a0, 3
    check_one_src(0x8511, make_pair(reg::a0, data), make_pair(reg::a0, data >> 4)); // 0x8511: c.srai a0, 4 ==> srli a0, a0, 4
    check_one_src(0x8585, make_pair(reg::a1, data), make_pair(reg::a1, data >> 1)); // 0x8585: c.srai a1, 1 ==> srli a1, a1, 1
}