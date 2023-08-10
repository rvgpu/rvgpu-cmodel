#include <gtest/gtest.h>

#include "sp/stream_processor.hpp"
#include "common/regid.hpp"

#define STACK_SIZE  2000

class ut_alu : public ::testing::Test {
protected:
    void SetUp() override {
        stack_pointer = (uint64_t)malloc(0x2000);
        stack_pointer += 0x1000;

        m_dec = new dec();
        m_alu = new alu(0);
        m_reg = new register_file();
    }
    void TearDown() override {
        delete m_dec;
        delete m_alu;
        delete m_reg;
    }

    void SetIReg(reg id, uint64_t data) {
        m_reg->write_ireg(0, static_cast<uint32_t>(id), data);
    }

    uint64_t GetIReg(reg id) {
        return m_reg->read_ireg(0, static_cast<uint32_t>(id));
    }

    void ExecuateInst() {
        m_reg->write_ireg(0, static_cast<uint32_t>(reg::sp), stack_pointer);

        // Run Instruction
        uint32_t instcode = insts.front();
        inst_issue to_issue = m_dec->decode_inst(instcode);
        m_reg->register_stage(0, to_issue);

        if (to_issue.type == encoding::INST_TYPE_ALU) {
            writeback_t res = m_alu->run(to_issue);
            m_reg->write(0, res.rid, res.wdata);
        } else {
            printf("NOT A ALU Instruction\n");
        }
    }

    dec *m_dec;
    alu *m_alu;
    register_file *m_reg;

    uint64_t npc;
    std::vector<uint32_t> insts;

    uint64_t stack_pointer;
};
