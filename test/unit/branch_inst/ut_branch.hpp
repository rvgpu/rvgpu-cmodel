#include <gtest/gtest.h>

#include "common/regid.hpp"
#include "simt/warp.hpp"

#define STACK_SIZE  2000

class ut_branch : public ::testing::Test {
protected:
    void SetUp() override {
        stack_pointer = (uint64_t)malloc(0x2000);
        stack_pointer += 0x1000;

        m_reg = new register_file();
        m_warp = new warp(m_reg);
    }
    void TearDown() override {
        delete m_reg;
        delete m_warp;
    }

    void SetIReg(reg id, uint64_t data) {
        m_warp->m_reg->write(0, static_cast<uint32_t>(id), data);
    }

    uint64_t GetIReg(reg id) {
        return m_warp->m_reg->read(0, static_cast<uint32_t>(id));
    }

    uint64_t GetPC() {
        return (uint64_t)npc;
    }

    void ExecuateInst() {
        m_warp->m_reg->write(0, static_cast<uint32_t>(reg::sp), stack_pointer);
        m_warp->m_reg->write(0, static_cast<uint32_t>(reg::zero), 0);
        // Run Instruction
        uint32_t instcode = insts.front();
        m_warp->pc = (uint64_t)insts.data();
        inst_issue to_issue = m_warp->m_dec->decode_inst(instcode);
        EXPECT_EQ(to_issue.type, encoding::INST_TYPE_BRANCH);

        m_reg->register_stage(0, to_issue);
        npc = m_warp->branch(to_issue, 0);
    }

    warp *m_warp;
    register_file *m_reg;

    uint64_t npc;
    std::vector<uint32_t> insts;

    uint64_t stack_pointer;
};
