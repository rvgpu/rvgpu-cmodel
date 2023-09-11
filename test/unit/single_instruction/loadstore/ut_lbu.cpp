#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_ld) {
    // 0x01014503: lbu a0, 16(sp)
    uint32_t *addr = (uint32_t *)(GetSP() + 16);
    *addr = 0x12345678;
    test_instruction(0x01014503, IN(reg::sp, GetSP()), RES(reg::a0, 0x78));
}