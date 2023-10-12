#include "ut_inst.hpp"


TEST_F(ut_inst, decode_and_execute_rv64i_ld_treg) {
    preload_register(special_reg::t0, 12);
    //0x0000058b rvg.ldtreg a1, 0
    test_instruction(0x58b, RES(reg::a1, 12));
}