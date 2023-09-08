#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_addi) {
    //addi bits: 0xfff50513  #addi a0, a0, -1

    test_instruction(0xfff50513, IN(reg::a0, 11),  RES(reg::a0, 11 - 1));
    test_instruction(0xfff50513, IN(reg::a0, -11), RES(reg::a0, -11 - 1));
    test_instruction(0xfff50513, IN(reg::a0, 0),   RES(reg::a0, 0 - 1));

    //bits: 0x000b0513 # mv a0, s6  pseudoinstruction of addi rd, rs, 0
    test_instruction(0x000b0513, IN(reg::s6, 11), RES(reg::a0, 11 + 0));

    // 0x07f00513 : li a0, 127 (addi x10, x0, 127)
    test_instruction(0x07f00513, RES(reg::a0, 127));
}