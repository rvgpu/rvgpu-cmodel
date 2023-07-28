#include <gtest/gtest.h>
#include <bit>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#include "common/softfloat_types.h"

TEST_F(ut_rv64_insns, decode_and_execute_rv64if_fmul_s) {
    // 0x00052a27: 27 2a 05 00   fsw ft0, 20(a0)
    insts.push_back(0x00052a27);
    LoadInst();

    float *addr = (float *)malloc(6 * sizeof(float));
    float in = 101.12f;

    float32_t a_u = { std::bit_cast<uint32_t>(in) };
    WRITE_REG(fetch.insn.rs1(), reinterpret_cast<uint64_t>(addr));
    WRITE_FREG(fetch.insn.rs2(), a_u);
    ExecuateInst();

    float result_float = std::bit_cast<float>(addr[5]);

    EXPECT_FLOAT_EQ(result_float, in);
}
