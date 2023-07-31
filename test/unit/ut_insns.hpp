#include <gtest/gtest.h>

#include "sp/stream_processor.hpp"
#include "common/regid.hpp"

#define STACK_SIZE  2000

class ut_insns : public ::testing::Test {
protected:
    void SetUp() override {
        stack_pointer = (uint64_t)malloc(0x1000);
        m_sp = new stream_processor();
    }
    void TearDown() override {
        delete m_sp;
    }

    void SetIReg(reg id, uint64_t data) {
        m_sp->m_reg->write_ireg<uint64_t>(0, static_cast<uint32_t>(id), data);
    }

    uint64_t GetIReg(reg id) {
        return m_sp->m_reg->read_ireg(0, static_cast<uint32_t>(id));
    }

    void ExecuateInst() {
        insts.push_back(0x00008067); // push ret
        m_sp->m_reg->write_ireg<uint64_t>(0, static_cast<uint32_t>(reg::sp), stack_pointer);
        m_sp->pc = (uint64_t)insts.data();

        // Run Instruction
        uint32_t instcode = *(uint32_t *)m_sp->pc;
        inst_issue to_issue = m_sp->m_dec->decode_inst(instcode);
        m_sp->pc = m_sp->execuator(to_issue);
    }

    stream_processor *m_sp;
    std::vector<uint32_t> insts;
    uint64_t stack_pointer;
};
