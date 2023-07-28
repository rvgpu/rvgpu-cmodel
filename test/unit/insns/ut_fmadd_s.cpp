#include <gtest/gtest.h>
#include <bit>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#include "common/softfloat_types.h"

TEST_F(ut_rv64_insns, decode_and_execute_rv64if_fmadd_s) {
    // 0x0020f043 : fmadd.s ft0, ft1, ft2, ft0
    insts.push_back(0x0020f043);
    LoadInst();

    float a = 1.1;
    float b = 2.1;
    float c = 3.1;
    float32_t a_u = { std::bit_cast<uint32_t>(a) };
    float32_t b_u = { std::bit_cast<uint32_t>(b) };
    float32_t c_u = { std::bit_cast<uint32_t>(c) };
    WRITE_FREG(fetch.insn.rs1(), a_u);
    WRITE_FREG(fetch.insn.rs2(), b_u);
    WRITE_FREG(fetch.insn.rs3(), c_u);
    ExecuateInst();
    float32_t result = READ_FREG_F(fetch.insn.rd());
    float result_float = std::bit_cast<float>(result.v);
    
    EXPECT_EQ(result_float, a * b + c);
}