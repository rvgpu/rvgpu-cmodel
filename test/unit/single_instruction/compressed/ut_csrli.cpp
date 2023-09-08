#include "ut_compressed.hpp"

TEST_F(ut_compressed, decode_and_execuate_c_srli) {
    check_one_src(0x8105, make_pair(reg::a0, 0x1234), make_pair(reg::a0, 0x1234 >> 1)); // 0x8111: c.srli a0, 1 ==> srli a0, a0, 1
    check_one_src(0x8109, make_pair(reg::a0, 0x1234), make_pair(reg::a0, 0x1234 >> 2)); // 0x8111: c.srli a0, 2 ==> srli a0, a0, 2
    check_one_src(0x810d, make_pair(reg::a0, 0x1234), make_pair(reg::a0, 0x1234 >> 3)); // 0x8111: c.srli a0, 3 ==> srli a0, a0, 3
    check_one_src(0x8111, make_pair(reg::a0, 0x1234), make_pair(reg::a0, 0x1234 >> 4)); // 0x8111: c.srli a0, 4 ==> srli a0, a0, 4
    check_one_src(0x8185, make_pair(reg::a1, 0x1234), make_pair(reg::a1, 0x1234 >> 1)); // 0x8185: c.srli a1, 1 ==> srli a1, a1, 1
}