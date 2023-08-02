#include <gtest/gtest.h>

#include "common/regid.hpp"
#include "sp/decoder.hpp"
#include "sp/register_file.hpp"
#include "sp/load_store.hpp"

#define STACK_SIZE  2000

class ut_loadstore : public ::testing::Test {
protected:
    void SetUp() override {
        stack_pointer = (uint64_t)malloc(0x2000);
        stack_pointer += 0x1000;

        m_dec = new dec();
        m_reg = new register_file();
        m_ls = new load_store(m_reg);
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
        EXPECT_EQ(to_issue.type, encoding::INST_TYPE_LS);

        to_issue.rs1 = m_reg->read_ireg(0, to_issue.rs1_id);
        if (to_issue.code == encoding::INST_LS_FSW) {
            to_issue.rs2 = m_reg->read_freg(0, to_issue.rs2_id);
        } else {
            to_issue.rs2 = m_reg->read_ireg(0, to_issue.rs2_id);
        }
        to_issue.rs3 = m_reg->read_ireg(0, to_issue.rs3_id);
        npc = m_ls->run(to_issue, 0);
    }

    dec *m_dec;
    register_file *m_reg;
    load_store *m_ls;

    uint64_t npc;
    std::vector<uint32_t> insts;

    uint64_t stack_pointer;
};
