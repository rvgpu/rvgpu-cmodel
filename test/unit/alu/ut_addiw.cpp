#include "ut_alu.hpp"

#define CHECK_ADD(a) do {                    \
        uint64_t result = 0;                    \
        SetIReg(rega, a);                       \
        ExecuateInst();                         \
        result = GetIReg(regr);                 \
        EXPECT_EQ(result, (a + 1));             \
    } while(0)

TEST_F(ut_alu, decode_and_execute_rv64i_addiw) {
    // 0x0017071b : addiw a4, a4, 1
    insts.push_back(0x0017071b);
    auto rega = reg::a4;
    auto regr = reg::a4;

    CHECK_ADD(11);
    CHECK_ADD(-11);
    CHECK_ADD(0);
}

TEST_F(ut_alu, decode_and_execute_rv64i_pseudo_sextw) {
    //bits: 0x0006869b  #sext.w a3, a3  pseudoinstruction of addiw rd, rs, 0
    // writes the sign-extension of the lower 32 bits of register rs1 into register rd
    insts.push_back(0x0006869b);
    auto rega = reg::a3;
    auto regr = reg::a3;

    uint64_t result = 0;
    SetIReg(rega, 11);
    ExecuateInst();
    result = GetIReg(regr);
    EXPECT_EQ(result, 11);
}