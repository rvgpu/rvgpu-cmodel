#pragma once

#include <gtest/gtest.h>

#include "common/regid.hpp"
#include "common/utils.hpp"
#include "simt/simt.hpp"

#include "ut_rvcore.hpp"
#include "ut_inst_ref.hpp"
#include "ut_inst_io.hpp"

class ut_inst : public ::testing::Test {
protected:
    void SetUp() override {
        mem = (uint64_t)malloc(0x2000);
        stack_pointer = mem + 0x1000;

        m_cpu = new rvcore();
    }
    void TearDown() override {
        delete m_cpu;
        free((void *)(mem));
        stack_pointer = 0;
    }

    uint64_t GetSP() {
        return stack_pointer;
    }

    uint64_t GetInstAddr() {
        return (uint64_t)single_inst;
    }

    void exec_instruction(uint32_t inst, IN in1, IN in2) {
        // Initialize Instruction and register
        single_inst[0] = inst;
        m_cpu->SetReg(static_cast<uint32_t>(in1.first), in1.second);
        m_cpu->SetReg(static_cast<uint32_t>(in2.first), in2.second);

        // Execuate one instruction
        npc = m_cpu->execuate((uint64_t)single_inst);
    }
    void test_instruction(uint32_t inst, IN in1, IN in2, IN in3, RES reference) {
        // Initialize Instruction and register
        single_inst[0] = inst;
        m_cpu->SetReg(static_cast<uint32_t>(in1.first), in1.second);
        m_cpu->SetReg(static_cast<uint32_t>(in2.first), in2.second);
        m_cpu->SetReg(static_cast<uint32_t>(in3.first), in3.second);

        // Execuate one instruction
        npc = m_cpu->execuate((uint64_t)single_inst);

        // Check Result
        check_register(reference);
    }
    void test_instruction(uint32_t inst, IN in1, IN in2, RES reference) {
        // Initialize Instruction and register
        single_inst[0] = inst;
        m_cpu->SetReg(static_cast<uint32_t>(in1.first), in1.second);
        m_cpu->SetReg(static_cast<uint32_t>(in2.first), in2.second);

        // Execuate one instruction
        npc = m_cpu->execuate((uint64_t)single_inst);

        // Check Result
        check_register(reference);
    }
    void test_instruction(uint32_t inst, IN in, RES reference) {
        // Initialize Instruction and register
        single_inst[0] = inst;
        m_cpu->SetReg(static_cast<uint32_t>(in.first), in.second);

        // Execuate one instruction
        npc = m_cpu->execuate((uint64_t)single_inst);

        // Check Result
        check_register(reference);
    }
    void test_instruction(uint32_t inst, RES reference) {
        // Initialize Instruction
        single_inst[0] = inst;

        // Execuate one instruction
        npc = m_cpu->execuate((uint64_t)single_inst);

        // Check Result
        check_register(reference);
    }

private:
    rvcore *m_cpu;

    uint64_t npc;
    uint32_t single_inst[1];

    uint64_t stack_pointer;
    uint64_t mem;

    void check_register(RES reference) {
        uint32_t regid = static_cast<uint32_t>(reference.first);
        if (regid <= 31) {
            // Compare to inerger register
            EXPECT_EQ(m_cpu->GetReg(regid), reference.second);
        } else if (regid <= 63) {
            // Compare to float register
            EXPECT_DOUBLE_EQ(utils::ul2d(m_cpu->GetReg(regid)), utils::ul2d(reference.second));
        } else if (regid == 64){
            // Compare npc
            EXPECT_EQ(npc, reference.second);
        } else {
            printf("error to check regid\n");
            EXPECT_EQ(0, 1);            // here should be failed
        }
    }
};
