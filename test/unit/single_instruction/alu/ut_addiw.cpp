#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_addiw) {
    // 0x0017071b : addiw a4, a4, 1
    test_instruction(0x0017071b, IN(reg::a4, 11), RES(reg::a4, 11 + 1));
    test_instruction(0x0017071b, IN(reg::a4, -11), RES(reg::a4, -11 + 1));
    test_instruction(0x0017071b, IN(reg::a4, 0), RES(reg::a4, 0 + 1));

    // bits: 0x0006869b  #sext.w a3, a3  pseudoinstruction of addiw rd, rs, 0
    // writes the sign-extension of the lower 32 bits of register rs1 into register rd
    test_instruction(0x0006869b, IN(reg::a3, 11), RES(reg::a3, 11));
}