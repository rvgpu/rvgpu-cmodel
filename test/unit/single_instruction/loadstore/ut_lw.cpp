#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_lw) {
    // 0x00c92503 : lw a0, 12(s2)
    int32_t *addr = (int32_t *)(GetSP() + 12);
    *addr = 0x10001000;
    test_instruction(0x00c92503, IN(reg::s2, GetSP()), RES(reg::a0, 0x10001000));
}