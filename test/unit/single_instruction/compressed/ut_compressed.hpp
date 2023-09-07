#include "ut_inst.hpp"

class ut_compressed : public ut_inst {
public:
    void check_caddi(uint32_t inst, reg rd, uint64_t data, uint64_t result) {
        insts.push_back(inst);
        SetIReg(rd, data);
        ExecuateInst();
        uint64_t res = GetIReg(rd);
        EXPECT_EQ(res, result);
    }

    void check_cjal(uint32_t inst, int32_t imm) {
        uint64_t pc = 0;
        insts.push_back(inst);
        pc = (uint64_t)insts.data();
        ExecuateInst();
        EXPECT_EQ(GetPC(), pc + imm);
    }

    void check_cli(uint32_t inst, reg rd, uint64_t result) {
        insts.push_back(inst);
        ExecuateInst();
        uint64_t res = GetIReg(rd);
        EXPECT_EQ(res, result);
    }
};