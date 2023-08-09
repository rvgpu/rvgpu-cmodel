#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_loadstore.hpp"

TEST_F(ut_loadstore, decode_and_execute_rv64i_sw){
    // 0x00a58023       sb  a0, 0(a1)
    insts.push_back(0x00a58023);
    auto sp = (uint64_t)malloc(32);
    ((uint32_t *)sp)[0] = 0;

    SetIReg(reg::a0, 0x12345678);
    SetIReg(reg::a1, sp);
    ExecuateInst();
    EXPECT_EQ(*(int32_t*)((uint64_t)sp), 0x00000078);
}