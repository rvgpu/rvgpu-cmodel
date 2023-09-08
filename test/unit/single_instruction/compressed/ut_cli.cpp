#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_li) {
    // c.li ==> addi rd, x0, imm
    check_result(0x4541, std::make_pair(reg::x0, 0), std::make_pair(reg::a0, 16));  // 0x4541: c.li a0, 16
    check_result(0x5541, std::make_pair(reg::x0, 0), std::make_pair(reg::a0, -16)); // 0x4541: c.li a0, -16
}