#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64_div) {
    // 0x02c5c533 : div a0, a1, a2
    uint64_t a = 0x87654321000;
    test_instruction(0x02c5c533, IN(reg::a1, a), IN(reg::a2, 4), RES(reg::a0, ref::div_i64(a, 4)));
    test_instruction(0x02c5c533, IN(reg::a1, a), IN(reg::a2, -4), RES(reg::a0, ref::div_i64(a, -4)));
}

TEST_F(ut_inst, decode_and_execute_rv64_divu) {
    // 0x02c5d533 : divu a0, a1, a2
    uint64_t a = 0x87654321000;
    test_instruction(0x02c5d533, IN(reg::a1, a), IN(reg::a2, 4), RES(reg::a0, ref::div_u64(a, 4)));
    test_instruction(0x02c5d533, IN(reg::a1, a), IN(reg::a2, -4), RES(reg::a0, ref::div_u64(a, -4)));
}

TEST_F(ut_inst, decode_and_execute_rv64_divw) {
    // 0x02c5c53b : divw a0, a1, a2
    uint64_t a = 0x87654321000;
    test_instruction(0x02c5c53b, IN(reg::a1, a), IN(reg::a2, 4), RES(reg::a0, int32_t(a)/int32_t(4)));
    test_instruction(0x02c5c53b, IN(reg::a1, a), IN(reg::a2, -4), RES(reg::a0, int32_t(a)/int32_t(-4)));
}

TEST_F(ut_inst, decode_and_execute_rv64_divuw) {
    // 0x02c5d53b : div a0, a1, a2
    uint64_t a = 0x87654321000;
    test_instruction(0x02c5d53b, IN(reg::a1, a), IN(reg::a2, 4), RES(reg::a0, uint32_t(a)/uint32_t(4)));
    test_instruction(0x02c5d53b, IN(reg::a1, a), IN(reg::a2, -4), RES(reg::a0, uint32_t(a)/uint32_t(-4)));
}