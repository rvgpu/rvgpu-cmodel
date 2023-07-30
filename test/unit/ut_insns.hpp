#include <gtest/gtest.h>

#include "sp/stream_processor.hpp"

#define STACK_SIZE  2000
#define REG_x0  0
#define REG_ra  1
#define REG_sp  2
#define REG_gp  3
#define REG_tp  4
#define REG_t0  5
#define REG_t1  6
#define REG_t2  7
#define REG_fp  8
#define REG_s1  9
#define REG_a0  10
#define REG_a1  11
#define REG_a2  12
#define REG_a3  13
#define REG_a4  14
#define REG_a5  15
#define REG_a6  16
#define REG_a7  17
#define REG_s2  18
#define REG_s3  19
#define REG_s4  20
#define REG_s5  21
#define REG_s6  22
#define REG_s7  23
#define REG_s8  24
#define REG_s9  25
#define REG_s10 26
#define REG_s11 27
#define REG_t3  28
#define REG_t4  29
#define REG_t5  30
#define REG_t6  31



class ut_insns : public ::testing::Test {
protected:
    void SetUp() override {
        m_sp = new stream_processor();
    }
    void TearDown() override {
        delete m_sp;
    }

    void SetIReg(uint32_t id, uint64_t data) {
        m_sp->m_reg->write_ireg<uint64_t>(0, id, data);
    }

    uint64_t GetIReg(uint32_t id) {
        return m_sp->m_reg->read_ireg(0, id);
    }

    void ExecuateInst() {
        insts.push_back(0x00008067); // push ret
        m_sp->setup((uint64_t)insts.data(), 0, 0, 0);
        m_sp->run();
    }

    stream_processor *m_sp;
    std::vector<uint32_t> insts;
};