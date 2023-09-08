#include "ut_compressed.hpp"

TEST_F(ut_compressed, decode_and_execuate_c_li) {
    // c.li ==> addi rd, x0, imm
    check_addi(0x4541, make_pair(reg::x0, 0), make_pair(reg::a0, 16));  // 0x4541: c.li a0, 16
    check_addi(0x5541, make_pair(reg::x0, 0), make_pair(reg::a0, -16)); // 0x4541: c.li a0, -16
}