#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_bgeu) {
    // 0x0496f663 : bgeu a3, s1, 76
    test_instruction(0x0496f663, IN(reg::a3, 1), IN(reg::s1, 2), RES(reg::pc, GetInstAddr() + 4));
    test_instruction(0x0496f663, IN(reg::a3, 2), IN(reg::s1, 2), RES(reg::pc, GetInstAddr() + 76));
    test_instruction(0x0496f663, IN(reg::a3, 3), IN(reg::s1, 2), RES(reg::pc, GetInstAddr() + 76));
    test_instruction(0x0496f663, IN(reg::a3, 2), IN(reg::s1, 0), RES(reg::pc, GetInstAddr() + 76));
    test_instruction(0x0496f663, IN(reg::a3, 0), IN(reg::s1, 2), RES(reg::pc, GetInstAddr() + 4));
    test_instruction(0x0496f663, IN(reg::a3, 0), IN(reg::s1, 0), RES(reg::pc, GetInstAddr() + 76));
}