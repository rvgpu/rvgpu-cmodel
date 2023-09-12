#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_addi16sp) {
    // 0x0808: c.addi4spn a0, 16 ==> addi a0, sp, imm
    test_instruction(0x0808, IN(reg::sp, GetSP()), RES(reg::a0, GetSP() + 16));
}