#include <gtest/gtest.h>
#include <bit>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#include "common/softfloat_types.h"

TEST_F(ut_rv64_insns, decode_and_execute_rv64if_fadd_s) {
    // 0x00107053 : fadd.s f0, f0, f1
    insts.push_back(0x00107053);
    LoadInst();

    float a = 1.1;
    float b = 2.1;
    float32_t a_u = { std::bit_cast<uint32_t>(a) };
    float32_t b_u = { std::bit_cast<uint32_t>(b) };
    WRITE_FREG(fetch.insn.rs1(), a_u);
    WRITE_FREG(fetch.insn.rs2(), b_u);
    ExecuateInst();
    float32_t result = READ_FREG_F(fetch.insn.rd());
    float result_float = std::bit_cast<float>(result.v);
    
    EXPECT_EQ(result_float, a + b);
}