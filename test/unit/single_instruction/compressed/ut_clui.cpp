#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_lui) {
    // c.lui ==> addi rd, x0, uimm
    test_instruction(0x6541, std::make_pair(reg::x0, 0), std::make_pair(reg::a0, 16)); // 0x6541: c.lui a0, 16
    test_instruction(0x7541, std::make_pair(reg::x0, 0), std::make_pair(reg::a0, uint64_t(-16))); // 0x6541: c.lui a0, 16
}