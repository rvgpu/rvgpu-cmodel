#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_pseudo_ret) {
    // 0x00008067 : ret (jalr x0, x1, 0)
    test_instruction(0x8067, IN(reg::x1, 0x1111), RES(reg::pc, 0x1110));
}

TEST_F(ut_inst, decode_and_execute_rv64i_pseudo_jalr) {
    // 0x000080e7 : jalr ra (jalr x1, ra, 0)
    test_instruction(0x80e7, IN(reg::ra, 0x1111), RES(reg::pc, 0x1110));
    test_instruction(0x80e7, IN(reg::ra, 0x1111), RES(reg::x1, int64_t(single_inst) + 4));  // write pc + 4 to x1
}
