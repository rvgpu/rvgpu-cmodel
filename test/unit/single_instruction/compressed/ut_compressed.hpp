#include "ut_inst.hpp"

using namespace std;

class ut_compressed : public ut_inst {
public:
    void check_addi(uint32_t inst, pair<reg, uint64_t> in, pair<reg, uint64_t>result) {
        insts.push_back(inst);
        SetIReg(in.first, in.second);
        ExecuateInst();
        uint64_t res = GetIReg(result.first);
        EXPECT_EQ(res, result.second);
    }

    void check_cjal(uint32_t inst, int32_t imm) {
        uint64_t pc = 0;
        insts.push_back(inst);
        pc = (uint64_t)insts.data();
        ExecuateInst();
        EXPECT_EQ(GetPC(), pc + imm);
    }

    void check_one_src(uint32_t inst, pair<reg, uint64_t> in, pair<reg, uint64_t>reference) {
        insts.push_back(inst);
        SetIReg(in.first, in.second);
        ExecuateInst();
        uint64_t result = GetIReg(reference.first);
        EXPECT_EQ(result, reference.second);
    }

    void check_csrla() {

    }
};