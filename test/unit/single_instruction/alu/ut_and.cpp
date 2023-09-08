#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_and) {
    // 0x00c5f533 : and a0, a1, a2
    uint64_t a = 0xff876543210;
    uint64_t b = 0x123456780ff;
    test_instruction(0x00c5f533, IN(reg::a1, a), IN(reg::a2, b), RES(reg::a0, a & b));
}

TEST_F(ut_inst, decode_and_execute_rv64i_andi) {
    // 0x020bfb93 : andi s7, s7, 32
    test_instruction(0x020bfb93, IN(reg::s7, 33), RES(reg::s7, 33 & 32));
}