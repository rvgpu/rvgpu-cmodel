#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_ld) {
    // 0x39813a03 : ld s4, 920(sp)
    int64_t *addr = (int64_t *)(GetSP() + 920);
    *addr = 0x1000100010001000;
    test_instruction(0x39813a03, IN(reg::sp, GetSP()), RES(reg::s4, 0x1000100010001000));
}