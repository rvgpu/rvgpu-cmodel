#include <gtest/gtest.h>

#include "sp/stream_processor.hpp"

enum class reg {
    x0 = 0,
    ra,
    sp,
    gp,
    tp,
    t0,
    t1,
    t2,
    fp,
    s1,
    a0,
    a1,
    a2,
    a3,
    a4,
    a5,
    a6,
    a7,
    s2,
    s3,
    s4,
    s5,
    s6,
    s7,
    s8,
    s9,
    s10,
    s11,
    t3,
    t4,
    t5,
    t6
};

#define STACK_SIZE  2000

class ut_insns : public ::testing::Test {
protected:
    void SetUp() override {
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
        m_sp->pc = (uint64_t)insts.data();
        m_sp->run();
    }

    stream_processor *m_sp;
    std::vector<uint32_t> insts;
};