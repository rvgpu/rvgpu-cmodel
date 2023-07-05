#include <gtest/gtest.h>

#include "sm/compute_unit.h"

#define STACK_SIZE  2000

class ut_insns : public ::testing::Test {
protected:
    void SetUp() override {
        p = new class compute_unit();
        sp = (uint32_t*) malloc(STACK_SIZE * sizeof (uint32_t));
        SetspHighToMMU();
    }

    void TearDown() override {
        delete p;
        free(sp);
    }

    void LoadInst() {
        pc = (uint64_t)insts.data();
        fetch = p->load_insn(pc);
    }

    void ExecuateInst() {
        next_pc = p->execute_insn(pc, fetch);
        next_pc = (uint64_t)((uint32_t)next_pc - (uint32_t)pc) + pc;
    }

    void SetspHighToMMU() {
        uint64_t sp_high = (uint64_t)sp & (0xffffffffLU << 32U);
        MMU.set_base_addr(sp_high);
    }
    compute_unit *p;
    std::vector<uint32_t> insts;

    uint64_t pc;
    uint64_t next_pc;
    insn_fetch_t fetch;
    uint32_t *sp;
};
