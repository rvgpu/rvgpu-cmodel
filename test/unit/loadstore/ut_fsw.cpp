#include <gtest/gtest.h>
#include <bit>
#include "sm/compute_unit.h"
#include "ut_loadstore.hpp"

#include "common/softfloat_types.h"

TEST_F(ut_loadstore, decode_and_execute_rv64if_fsw) {
    // 0x00052a27: 27 2a 05 00   fsw ft0, 20(a0)
    insts.push_back(0x00052a27);

    uint32_t *addr = (uint32_t *)(GetStackPointer() + 20);

    SetIReg(reg::a0, GetStackPointer());
    SetFReg(fpreg::ft0, std::bit_cast<uint32_t>(1.1f));
    ExecuateInst();
    EXPECT_EQ(std::bit_cast<float>(*addr), 1.1f);
}
