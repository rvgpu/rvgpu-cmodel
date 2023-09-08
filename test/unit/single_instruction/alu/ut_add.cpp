#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_add) {
    //0x00d786b3 : add a3, a5, a3
    test_instruction(0x00d786b3, IN(reg::a5, 1), IN(reg::a3, 2), RES(reg::a3, 1 + 2));
}

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

TEST_F(ut_inst, decode_and_execute_rv64i_addiw) {
    // 0x0017071b : addiw a4, a4, 1
    test_instruction(0x0017071b, IN(reg::a4, 11), RES(reg::a4, 11 + 1));
    test_instruction(0x0017071b, IN(reg::a4, -11), RES(reg::a4, -11 + 1));
    test_instruction(0x0017071b, IN(reg::a4, 0), RES(reg::a4, 0 + 1));

    // bits: 0x0006869b  #sext.w a3, a3  pseudoinstruction of addiw rd, rs, 0
    // writes the sign-extension of the lower 32 bits of register rs1 into register rd
    test_instruction(0x0006869b, IN(reg::a3, 11), RES(reg::a3, 11));
}

TEST_F(ut_inst, decode_and_execute_rv64i_addw) {
    // 0x00e5053b : addw a0, a0, a4
    test_instruction(0x00e5053b, IN(reg::a0, 11), IN(reg::a4, 12), RES(reg::a0, 11 + 12));
    test_instruction(0x00e5053b, IN(reg::a0, -11), IN(reg::a4, 12), RES(reg::a0, -11 + 12));
    test_instruction(0x00e5053b, IN(reg::a0, 11), IN(reg::a4, -12), RES(reg::a0, 11 - 12));
    test_instruction(0x00e5053b, IN(reg::a0, 11), IN(reg::a4, 0), RES(reg::a0, 11 + 0));
    test_instruction(0x00e5053b, IN(reg::a0, 0), IN(reg::a4, 12), RES(reg::a0, 0 + 12));
}