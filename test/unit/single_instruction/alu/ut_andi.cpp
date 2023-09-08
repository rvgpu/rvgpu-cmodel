#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_andi) {
    // 0x020bfb93 : andi s7, s7, 32
    test_instruction(0x020bfb93, IN(reg::s7, 33), RES(reg::s7, 33 & 32));
}