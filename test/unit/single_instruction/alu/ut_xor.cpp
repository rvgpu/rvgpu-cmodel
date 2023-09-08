#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_xor) {
    // 0x00c5c533 xor a0, a1, a2
    test_instruction(0x00c5c533, IN(reg::a1, 0x88880000), IN(reg::a2, 0x87654321), RES(reg::a0, uint64_t(0x88880000) ^ uint64_t(0x87654321)));
}

TEST_F(ut_inst, decode_and_execute_rv64i_xori) {
    // 0x001aca93 : xori s5, s5, 1
    test_instruction(0x001aca93, IN(reg::s5, 7), RES(reg::s5, 6));
}