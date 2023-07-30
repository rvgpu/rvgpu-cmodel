#include <gtest/gtest.h>

#include "sp/stream_processor.hpp"

enum class reg {
    x0   = 0,
    zero = 0,
    x1   = 1,
    ra   = 1,
    x2   = 2,
    sp   = 2,
    x3   = 3,
    gp   = 3,
    x4   = 4,
    tp   = 4,
    x5   = 5,
    t0   = 5,
    x6   = 6,
    t1   = 6,
    x7   = 7,
    t2   = 7,
    x8   = 8,
    s0   = 8,
    fp   = 8,
    x9   = 9,
    s1   = 9,
    x10  = 10,
    a0   = 10,
    x11  = 11,
    a1   = 11,
    x12  = 12,
    a2   = 12,
    x13  = 13,
    a3   = 13,
    x14  = 14,
    a4   = 14,
    x15  = 15,
    a5   = 15,
    x16  = 16,
    a6   = 16,
    x17  = 17,
    a7   = 17,
    x18  = 18,
    s2   = 18,
    x19  = 19,
    s3   = 19,
    x20  = 20,
    s4   = 20,
    x21  = 21,
    s5   = 21,
    x22  = 22,
    s6   = 22,
    x23  = 23,
    s7   = 23,
    x24  = 24,
    s8   = 24,
    x25  = 25,
    s9   = 25,
    x26  = 26,
    s10  = 26,
    x27  = 27,
    s11  = 27,
    x28  = 28,
    t3   = 28,
    x29  = 29,
    t4   = 29,
    x30  = 30,
    t5   = 30,
    x31  = 31,
    t6   = 31
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