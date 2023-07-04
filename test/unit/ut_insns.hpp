#include <gtest/gtest.h>

#include "sm/compute_unit.h"

class ut_insns : public ::testing::Test {
protected:
    void SetUp() override {
        p = new class compute_unit();
    }

    void TearDown() override {
        delete p;
    }

    void LoadInst() {
        pc = (uint64_t)insts.data();
        fetch = p->load_insn(pc);
    }

    void ExecuateInst() {
        next_pc = p->execute_insn(pc, fetch);
        next_pc = (uint64_t)((uint32_t)next_pc - (uint32_t)pc) + pc;
    }

    compute_unit *p;
    std::vector<uint32_t> insts;

    uint64_t pc;
    uint64_t next_pc;
    insn_fetch_t fetch;
};
