#include <gtest/gtest.h>

#include "sm/compute_unit.h"

#define STACK_SIZE  2000

class ut_insns : public ::testing::Test {
protected:
    void LoadInst() {
        pc = (uint64_t)insts.data();
        fetch = p->load_insn(pc);
    }

    void ExecuateInst() {
        next_pc = p->execute_insn(pc, fetch);
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

class ut_rv32_insns : public ut_insns {
protected:
    void SetUp() override {
        auto isa_parser = new isa_parser_t("RV32I");
        p = new class compute_unit(isa_parser);
        sp = (uint32_t*) malloc(STACK_SIZE * sizeof (uint32_t));
        SetspHighToMMU();
    }
    void TearDown() override {
        delete p;
        free(sp);
    }
};

class ut_rv64_insns : public ut_insns {
protected:
    void SetUp() override {
        auto isa_parser = new isa_parser_t("RV64I");
        p = new class compute_unit(isa_parser);
        sp = (uint32_t*) malloc(STACK_SIZE * sizeof (uint32_t));
        SetspHighToMMU();
    }
    void TearDown() override {
        delete p;
        free(sp);
    }
};