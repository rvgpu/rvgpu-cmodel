#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_pseudo_sgtz) {
    uint64_t a;
    //bits: 0x00a02ab3    #sgtz s5, a0
    //sgtz is pseudo instructions, same as: slt rd, x0, rs2, Set if > zero
    a = 0xffffffffffffffff;
    test_instruction(0x00a02ab3, IN(reg::a0, a), RES(reg::s5, 0));
    a = 0x7fffffffffffffff;
    test_instruction(0x00a02ab3, IN(reg::a0, a), RES(reg::s5, 1));
}

TEST_F(ut_inst, decode_and_execute_rv64i_slti) {
    // 0x0085a513 slti a0, a1, 8
    test_instruction(0x0085a513, IN(reg::a1, 6), RES(reg::a0, 6 < 8));
    test_instruction(0x0085a513, IN(reg::a1, 10), RES(reg::a0, 10 < 8));
}

TEST_F(ut_inst, decode_and_execute_rv64i_sltiu) {
    // 0x0085b513 sltiu a0, a1, 8
    test_instruction(0x0085b513, IN(reg::a1, 6), RES(reg::a0, 6 < 8));
    test_instruction(0x0085b513, IN(reg::a1, 10), RES(reg::a0, 10 < 8));
}

TEST_F(ut_inst, decode_and_execute_rv64i_sltu) {
    // snez: 0xa03533; # snez a0, a0 ==> sltu a0, x0, a0
    test_instruction(0xa03533, IN(reg::a0, 0), RES(reg::a0, 0 < 0));
    test_instruction(0xa03533, IN(reg::a0, 1), RES(reg::a0, 0 < 1));
}
