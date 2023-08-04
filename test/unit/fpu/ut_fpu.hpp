#include <gtest/gtest.h>

#include "sp/stream_processor.hpp"
#include "common/regid.hpp"

#define STACK_SIZE  2000

class ut_fpu : public ::testing::Test {
protected:
    void SetUp() override {
        stack_pointer = (uint64_t)malloc(0x2000);
        stack_pointer += 0x1000;

        m_dec = new dec();
        m_fpu = new fpu(0);
        m_reg = new register_file();
    }
    void TearDown() override {
        delete m_dec;
        delete m_fpu;
        delete m_reg;
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

    void ExecuateInst() {
        m_reg->write_ireg(0, static_cast<uint32_t>(reg::sp), stack_pointer);

        // Run Instruction
        uint32_t instcode = insts.front();
        inst_issue to_issue = m_dec->decode_inst(instcode);
        if (to_issue.type == encoding::INST_TYPE_FPU) {
            to_issue.rs1 = m_reg->read_ireg(0, to_issue.rs1_id);
            to_issue.rs2 = m_reg->read_ireg(0, to_issue.rs2_id);
            to_issue.rs3 = m_reg->read_ireg(0, to_issue.rs3_id);
            to_issue.frs1 = m_reg->read_freg(0, to_issue.rs1_id);
            to_issue.frs2 = m_reg->read_freg(0, to_issue.rs2_id);
            to_issue.frs3 = m_reg->read_freg(0, to_issue.rs3_id);
            uint64_t res = m_fpu->run(to_issue);
            m_reg->write_freg(0, to_issue.rd, res);
        } else {
            printf("NOT A FPU Instruction\n");
        }
    }

    dec *m_dec;
    fpu *m_fpu;
    register_file *m_reg;

    uint64_t npc;
    std::vector<uint32_t> insts;

    uint64_t stack_pointer;
};
