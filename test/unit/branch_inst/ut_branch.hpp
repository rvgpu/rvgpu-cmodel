#include <gtest/gtest.h>

#include "common/regid.hpp"
#include "sp/stream_processor.hpp"

#define STACK_SIZE  2000

class ut_branch : public ::testing::Test {
protected:
    void SetUp() override {
        stack_pointer = (uint64_t)malloc(0x2000);
        stack_pointer += 0x1000;

        m_dec = new dec();
        m_sp = new stream_processor();
    }
    void TearDown() override {
        delete m_dec;
    }

    void SetIReg(reg id, uint64_t data) {
        m_sp->m_reg->write_ireg<uint64_t>(0, static_cast<uint32_t>(id), data);
    }

    uint64_t GetIReg(reg id) {
        return m_sp->m_reg->read_ireg(0, static_cast<uint32_t>(id));
    }

    uint64_t GetPC() {
        return (uint64_t)npc;
    }

    void ExecuateInst() {
        m_sp->m_reg->write_ireg<uint64_t>(0, static_cast<uint32_t>(reg::sp), stack_pointer);
        m_sp->m_reg->write_ireg<uint64_t>(0, static_cast<uint32_t>(reg::zero), 0);
        // Run Instruction
        uint32_t instcode = insts.front();
        m_sp->pc = (uint64_t)insts.data();
        inst_issue to_issue = m_dec->decode_inst(instcode);
        EXPECT_EQ(to_issue.type, encoding::INST_TYPE_BRANCH);

        to_issue.rs1 = m_sp->m_reg->read_ireg(0, to_issue.rs1_id);
        to_issue.rs2 = m_sp->m_reg->read_ireg(0, to_issue.rs2_id);
        to_issue.rs3 = m_sp->m_reg->read_ireg(0, to_issue.rs3_id);
        npc = m_sp->branch(to_issue);
    }

    dec *m_dec;
    stream_processor *m_sp;

    uint64_t npc;
    std::vector<uint32_t> insts;

    uint64_t stack_pointer;
};
