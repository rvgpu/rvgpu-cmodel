#include <gtest/gtest.h>

#include "common/regid.hpp"
#include "rvcore/decoder.hpp"
#include "rvcore/load_store.hpp"
#include "sp/register_file.hpp"

#define STACK_SIZE  2000

class ut_loadstore : public ::testing::Test {
protected:
    void SetUp() override {
        stack_pointer = (uint64_t)malloc(0x2000);
        stack_pointer += 0x1000;

        m_dec = new dec();
        m_reg = new register_file();
        m_ls = new load_store();
    }
    void TearDown() override {
        delete m_dec;
    }

    void SetIReg(reg id, uint64_t data) {
        m_reg->write_ireg(0, static_cast<uint32_t>(id), data);
    }

    uint64_t GetIReg(reg id) {
        return m_reg->read_ireg(0, static_cast<uint32_t>(id));
    }

    void SetFReg(fpreg id, uint64_t data) {
        m_reg->write_freg(0, static_cast<uint32_t>(id), data);
    }

    uint64_t GetFReg(fpreg id) {
        return m_reg->read_freg(0, static_cast<uint32_t>(id));
    }

    uint64_t GetPC() {
        return (uint64_t)npc;
    }

    uint64_t GetStackPointer() {
        return stack_pointer;
    }

    void ExecuateInst() {
        m_reg->write_ireg(0, static_cast<uint32_t>(reg::sp), stack_pointer);
        m_reg->write_ireg(0, static_cast<uint32_t>(reg::zero), 0);
        // Run Instruction
        uint32_t instcode = insts.front();
        inst_issue to_issue = m_dec->decode_inst(instcode);
        m_reg->register_stage(0, to_issue);
        EXPECT_EQ(to_issue.type, encoding::INST_TYPE_LS);

        writeback_t res = m_ls->run(to_issue);
        m_reg->write(0, res.rid, res.wdata);
    }

    dec *m_dec;
    register_file *m_reg;
    load_store *m_ls;

    uint64_t npc;
    std::vector<uint32_t> insts;

    uint64_t stack_pointer;
};
