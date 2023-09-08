#include "ut_compressed.hpp"

TEST_F(ut_compressed, decode_and_execuate_c_lui) {
    // c.lui ==> addi rd, x0, uimm
    check_addi(0x6541, make_pair(reg::x0, 0), make_pair(reg::a0, 16)); // 0x6541: c.lui a0, 16
    check_addi(0x7541, make_pair(reg::x0, 0), make_pair(reg::a0, uint64_t(-16))); // 0x6541: c.lui a0, 16
}