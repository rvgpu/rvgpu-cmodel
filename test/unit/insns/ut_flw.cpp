#include <gtest/gtest.h>
#include <bit>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#include "common/softfloat_types.h"

TEST_F(ut_rv64_insns, decode_and_execute_rv64if_fmul_s) {
    // 0x00051007:   07 a0 05 00   flw ft0, 0(a1)
    // 0x0045a007:   07 a0 45 00   flw ft0, 4(a1)
    insts.push_back(0x0045a007);
    LoadInst();

    float *addr = (float *)malloc(4 * sizeof(float));
    addr[1] = 200.0f;

    WRITE_REG(fetch.insn.rs1(), reinterpret_cast<uint64_t>(addr));
    ExecuateInst();

    float32_t result = READ_FREG_F(fetch.insn.rd());
    float result_float = std::bit_cast<float>(result.v);
    
    EXPECT_EQ(result_float, addr[1]);
}
