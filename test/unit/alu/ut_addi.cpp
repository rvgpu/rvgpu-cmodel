#include "ut_alu.hpp"

#define CHECK_ADD(a) do {                    \
        uint64_t result = 0;                    \
        SetIReg(rega, a);                       \
        ExecuateInst();                         \
        result = GetIReg(regr);                 \
        EXPECT_EQ(result, (a - 1));             \
    } while(0)

TEST_F(ut_alu, decode_and_execute_rv64i_addi) {
    //addi bits: 0xfff50513  #addi a0, a0, -1
    insts.push_back(0xfff50513);
    auto rega = reg::a0;
    auto regr = reg::a0;

    CHECK_ADD(11);
    CHECK_ADD(-11);
    CHECK_ADD(0);
}

TEST_F(ut_alu, decode_and_execute_rv64i_pseudo_mv) {
    //bits: 0x000b0513 #mv a0, s6  pseudoinstruction of addi rd, rs, 0
    insts.push_back(0x000b0513);    
    auto rega = reg::s6;
    auto regr = reg::a0;

    uint64_t result = 0;
    SetIReg(rega, 11);
    ExecuateInst();
    result = GetIReg(regr);
    EXPECT_EQ(result, 11);
}

TEST_F(ut_alu, decode_and_execute_rv64i_pseudo_li) {
    // 0x07f00513 : li a0, 127 (addi x10, x0, 127)
    insts.push_back(0x07f00513);
    SetIReg(reg::x0, 0x0);
    ExecuateInst();

    uint64_t result = GetIReg(reg::x10);
    EXPECT_EQ(result, 127);
}