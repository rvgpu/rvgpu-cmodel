#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64id_fld) {
    // 0x0045b007: fld ft0, 4(a1)
    insts.push_back(0x0045b007);

    uint64_t *addr = (uint64_t *)(GetStackPointer() + 4);
    *addr = std::bit_cast<uint64_t>(1.1);

    auto regr = fpreg::ft0;
    uint64_t result = 0;
    SetIReg(reg::a1, GetStackPointer());
    ExecuateInst();
    result = GetFReg(regr);
    EXPECT_EQ(std::bit_cast<double>(result), 1.1);
}
