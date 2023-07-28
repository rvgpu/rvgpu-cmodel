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

TEST_F(ut_rv64_insns, decode_and_execute_rv64im_mul) {
    // 0x02b50533 : mul	a0, a0, a1 
    insts.push_back(0x02b50533);
    uint64_t result;
    LoadInst();

    CHECK_MUL(1, 2);
    CHECK_MUL(2, 1);
    CHECK_MUL(-11, 12);
    CHECK_MUL(11, -12);
    CHECK_MUL(-11, -12);
}