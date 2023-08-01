#include <gtest/gtest.h>
#include "sm/compute_unit.h"
#include "ut_alu.hpp"

TEST_F(ut_alu, decode_and_execute_rv64i_pseudo_sgtz_set_to_0) {
    //bits: 0x00a02ab3    #sgtz s5, a0
    //sgtz is pseudoinstructions inst, same as: slt rd, x0, rs2, Set if > zero
    insts.push_back(0x00a02ab3);
    SetIReg(reg::a0, 0xffffffffffffffff);

    ExecuateInst();
    auto res = GetIReg(reg::s5);
    EXPECT_EQ(res, 0);
}

TEST_F(ut_alu, decode_and_execute_rv64i_pseudo_sgtz_set_to_1) {
    //bits: 0x00a02ab3    #sgtz s5, a0
    //sgtz is pseudoinstructions inst, same as: slt rd, x0, rs, Set if > zero
    insts.push_back(0x00a02ab3);
    insts.push_back(0x00a02ab3);
    SetIReg(reg::a0, 0x7fffffffffffffff);

    ExecuateInst();
    auto res = GetIReg(reg::s5);
    EXPECT_EQ(res, 1);
}
