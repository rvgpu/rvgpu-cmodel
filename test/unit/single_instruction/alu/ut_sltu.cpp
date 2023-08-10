#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_pseudo_snez_set_to_1) {
    // snez: 0xa03533; # snez    a0, a0
    // SNEZ rd, rs;  says: rs != 0 ? write 1 to rd : write 0 to rd;  which is assembler pseudoinstruction
    // is same with SLTU rd, x0, rs2 ; SLTU perform unsigned compares respectively,
    // writing 1 to rd if rs1 < rs2, 0 otherwise
    insts.push_back(0xa03533);
    auto rega = reg::a0;
    auto regr = reg::a0;

    uint64_t result = 0;
    SetIReg(rega, 1);
    ExecuateInst();
    result = GetIReg(regr);
    EXPECT_EQ(result, 1);
}

TEST_F(ut_inst, decode_and_execute_rv64i_pseudo_snez_set_to_0) {
    // snez: 0xa03533; # snez a0, a0
    insts.push_back(0xa03533);
    auto rega = reg::a0;
    auto regr = reg::a0;

    uint64_t result = 0;
    SetIReg(rega, 0);
    ExecuateInst();
    result = GetIReg(regr);
    EXPECT_EQ(result, 0);
}