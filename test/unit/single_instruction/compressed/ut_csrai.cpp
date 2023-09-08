#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_srai) {
    uint32_t data = 0x1234;
    test_instruction(0x8505, std::make_pair(reg::a0, data), std::make_pair(reg::a0, ref::srai(data, 1))); // 0x8505: c.srai a0, 1 ==> srli a0, a0, 1
    test_instruction(0x8509, std::make_pair(reg::a0, data), std::make_pair(reg::a0, ref::srai(data, 2))); // 0x8509: c.srai a0, 2 ==> srli a0, a0, 2
    test_instruction(0x850d, std::make_pair(reg::a0, data), std::make_pair(reg::a0, ref::srai(data, 3))); // 0x850d: c.srai a0, 3 ==> srli a0, a0, 3
    test_instruction(0x8511, std::make_pair(reg::a0, data), std::make_pair(reg::a0, ref::srai(data, 4))); // 0x8511: c.srai a0, 4 ==> srli a0, a0, 4
    test_instruction(0x8585, std::make_pair(reg::a1, data), std::make_pair(reg::a1, ref::srai(data, 1))); // 0x8585: c.srai a1, 1 ==> srli a1, a1, 1
}