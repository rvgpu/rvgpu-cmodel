#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#include "common/softfloat_types.h"

TEST_F(ut_rv64_insns, decode_and_execute_rv64if_fmul_s) {
    // 0x10b6f6d3 : fmul.s fa3, fa3, fa1
    insts.push_back(0x10b6f6d3);
    LoadInst();

    float a = 1.1;
    float b = 2.1;
    float32_t a_u = { *((uint32_t *)(&a)) };
    float32_t b_u = { *((uint32_t *)(&b)) };
    WRITE_FREG(fetch.insn.rs1(), a_u);
    WRITE_FREG(fetch.insn.rs2(), b_u);
    ExecuateInst();
    float32_t result = READ_FREG_F(fetch.insn.rd());
    float result_float = *((float *)(&(result.v)));
    
    EXPECT_EQ(result_float, a * b);
}