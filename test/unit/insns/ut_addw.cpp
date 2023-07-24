#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#define CHECK_ADD(a, b) do { \
        WRITE_REG(fetch.insn.rs1(), a); \
        WRITE_REG(fetch.insn.rs2(), b); \
        ExecuateInst();           \
        result = READ_REG(fetch.insn.rd()); \
        EXPECT_EQ(result, (a + b)); \
    } while(0)

TEST_F(ut_rv64_insns, decode_and_execute_rv64i_addw) {
    // 0x00e5053b : addw a0, a0, a4
    insts.push_back(0x00e5053b);
    uint64_t result;
    LoadInst();

    CHECK_ADD(1, 2);
    CHECK_ADD(2, 1);
    CHECK_ADD(-11, 12);
    CHECK_ADD(11, -12);
    CHECK_ADD(-11, -12);
}