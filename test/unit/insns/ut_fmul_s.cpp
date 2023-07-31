#include <gtest/gtest.h>
#include <bit>
#include "sm/compute_unit.h"
#include "ut_insns.hpp"

#include "common/softfloat_types.h"

TEST_F(ut_insns, decode_and_execute_rv64if_fmul_s) {
    // 0x10b6f6d3 : fmul.s fa3, fa3, fa1
    insts.push_back(0x10b6f6d3);
    
    float a = 1.1f;
    float b = 2.1f;
    SetFReg(fpreg::fa3, std::bit_cast<uint32_t>(a));
    SetFReg(fpreg::fa1, std::bit_cast<uint32_t>(b));

    ExecuateInst();

    uint32_t res = GetFReg(fpreg::fa3);
    EXPECT_FLOAT_EQ(std::bit_cast<float>(res), a * b);
}