#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_bltu) {
    // 0x009ce463 : bltu s9, s1, 8
    test_instruction(0x009ce463, IN(reg::s9, 1), IN(reg::s1, 2), RES(reg::pc, int64_t(single_inst) + 8));
    test_instruction(0x009ce463, IN(reg::s9, 2), IN(reg::s1, 2), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0x009ce463, IN(reg::s9, 3), IN(reg::s1, 2), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0x009ce463, IN(reg::s9, 2), IN(reg::s1, 0), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0x009ce463, IN(reg::s9, 0), IN(reg::s1, 2), RES(reg::pc, int64_t(single_inst) + 8));
    test_instruction(0x009ce463, IN(reg::s9, 0), IN(reg::s1, 0), RES(reg::pc, int64_t(single_inst) + 4));
}