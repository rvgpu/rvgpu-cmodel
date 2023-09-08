#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64_rem) {
    // 0x02c5e533 : rem a0, a1, a2
    uint64_t a = 0x87654321000;
    test_instruction(0x02c5e533, IN(reg::a1, a), IN(reg::a2, 4), RES(reg::a0, a % 4));
    test_instruction(0x02c5e533, IN(reg::a1, a), IN(reg::a2, -4), RES(reg::a0, int64_t(a) % (-4)));
}

TEST_F(ut_inst, decode_and_execute_rv64_remu) {
    // 0x02c5f533 : remu a0, a1, a2
    uint64_t a = 0x87654321000;
    test_instruction(0x02c5f533, IN(reg::a1, a), IN(reg::a2, 4), RES(reg::a0, a % 4));
    test_instruction(0x02c5f533, IN(reg::a1, a), IN(reg::a2, -4), RES(reg::a0, uint64_t(a) % uint64_t(-4)));
}

TEST_F(ut_inst, decode_and_execute_rv64_remw) {
    // 0x02c5e53b : remw a0, a1, a2
    uint64_t a = 0x87654321000;
    test_instruction(0x02c5e53b, IN(reg::a1, a), IN(reg::a2, 4), RES(reg::a0, int32_t(a) % 4));
    test_instruction(0x02c5e53b, IN(reg::a1, a), IN(reg::a2, -4), RES(reg::a0, int32_t(a) % int32_t(-4)));
}

TEST_F(ut_inst, decode_and_execute_rv64_remuw) {
    // 0x02c5f53b : remuw a0, a1, a2
    uint64_t a = 0x87654321000;
    test_instruction(0x02c5f53b, IN(reg::a1, a), IN(reg::a2, 4), RES(reg::a0, int32_t(a) % 4));
    test_instruction(0x02c5f53b, IN(reg::a1, a), IN(reg::a2, -4), RES(reg::a0, uint32_t(a) % uint32_t(-4)));
}