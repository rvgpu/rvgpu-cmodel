#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#define CHECK_MUL(a, b) do { \
        WRITE_REG(fetch.insn.rs1(), a); \
        WRITE_REG(fetch.insn.rs2(), b); \
        ExecuateInst();           \
        result = READ_REG(fetch.insn.rd()); \
        EXPECT_EQ(result, (a * b)); \
    } while(0)

TEST_F(ut_rv64_insns, decode_and_execute_rv64im_mulw) {
    // 0x03da8c3b : mulw s8, s5, t4
    insts.push_back(0x03da8c3b);
    uint64_t result;
    LoadInst();

    CHECK_MUL(1, 2);
    CHECK_MUL(2, 1);
    CHECK_MUL(-11, 12);
    CHECK_MUL(11, -12);
    CHECK_MUL(-11, -12);
}