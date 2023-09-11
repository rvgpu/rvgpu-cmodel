#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_bgeu) {
    // 63 56 b5 02   bge a0, a1, 44
    test_instruction(0x02b55663, IN(reg::a0, 1), IN(reg::a1, 2), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0x02b55663, IN(reg::a0, 1), IN(reg::a1, -2), RES(reg::pc, int64_t(single_inst) + 44));
    test_instruction(0x02b55663, IN(reg::a0, 2), IN(reg::a1, 1), RES(reg::pc, int64_t(single_inst) + 44));
    test_instruction(0x02b55663, IN(reg::a0, 2), IN(reg::a1, -1), RES(reg::pc, int64_t(single_inst) + 44));
    test_instruction(0x02b55663, IN(reg::a0, -1), IN(reg::a1, 2), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0x02b55663, IN(reg::a0, -1), IN(reg::a1, -2), RES(reg::pc, int64_t(single_inst) + 44));
    test_instruction(0x02b55663, IN(reg::a0, -2), IN(reg::a1, 1), RES(reg::pc, int64_t(single_inst) + 4));
    test_instruction(0x02b55663, IN(reg::a0, -2), IN(reg::a1, -1), RES(reg::pc, int64_t(single_inst) + 4));
}
