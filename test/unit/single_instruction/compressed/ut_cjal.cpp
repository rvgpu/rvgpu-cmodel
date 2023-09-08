#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execuate_c_jal) {
    check_result(0x2801, std::make_pair(reg::pc, GetPC() + 16));    // 0x2801: cjal 16
    check_result(0x3fc5, std::make_pair(reg::pc, GetPC() - 16));    // 0x3fc5: c.jal -16
}