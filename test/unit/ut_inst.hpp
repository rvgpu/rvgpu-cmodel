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
        stack_pointer = (uint64_t)malloc(0x2000);
        stack_pointer += 0x1000;

        m_cpu = new rvcore();
        m_dec = new decoder();
        m_alu = new alu(0);
        m_fpu = new fpu(0);
        m_ls = new load_store();
        m_branch = new branch();
        m_reg = new register_file();
    }
    void TearDown() override {
        delete m_dec;
        delete m_alu;
        delete m_reg;
    }

    void SetIReg(reg id, uint64_t data) {
        m_reg->write(0, static_cast<uint32_t>(id), data);
    }

    uint64_t GetIReg(reg id) {
        return m_reg->read(0, static_cast<uint32_t>(id));
    }

    void SetFReg(fpreg id, uint64_t data) {
        m_reg->write(0, static_cast<uint32_t>(id), data);
    }

    uint64_t GetFReg(fpreg id) {
        return m_reg->read(0, static_cast<uint32_t>(id));
    }

    uint64_t GetStackPointer() {
        return stack_pointer;
    }

    void ExecuateInst() {
        m_reg->write(0, static_cast<uint32_t>(reg::sp), stack_pointer);

        // Run Instruction
        uint32_t instcode = insts.front();
        inst_issue to_issue = m_dec->decode_inst(instcode);
        m_reg->register_stage(0, to_issue);
        to_issue.currpc = (uint64_t)insts.data();

        writeback_t wb = {};
        switch (to_issue.type) {
            case encoding::INST_TYPE_ALU: {
                wb = m_alu->run(to_issue);
                break;
            }
            case encoding::INST_TYPE_FPU: {
                wb = m_fpu->run(to_issue);
                break;
            }
            case encoding::INST_TYPE_LS: {
                wb = m_ls->run(to_issue);
                break;
            }
            case encoding::INST_TYPE_BRANCH: {
                wb = m_branch->run(to_issue, npc);
                break;
            }
            case encoding::INST_TYPE_NOP: {
                break;
            }
            default:
                RVGPU_ERROR_PRINT("Instruction ERROR: %x\n", to_issue.bits);
                break;
        }

        m_reg->write(0, wb.rid, wb.wdata);
        insts.clear();
    }

    uint64_t GetPC() {
        return npc;
    }

    uint64_t GetSP() {
        return stack_pointer;
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
        insts.clear();
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
        insts.clear();
    }

    void test_instruction(uint32_t inst, IN in, RES reference) {
        // Initialize Instruction and register
        single_inst[0] = inst;
        m_cpu->SetReg(static_cast<uint32_t>(in.first), in.second);

        // Execuate one instruction
        npc = m_cpu->execuate((uint64_t)single_inst);

        // Check Result
        check_register(reference);
        insts.clear();
    }

    void test_instruction(uint32_t inst, RES reference) {
        // Initialize Instruction
        single_inst[0] = inst;

        // Execuate one instruction
        npc = m_cpu->execuate((uint64_t)single_inst);

        // Check Result
        check_register(reference);
    }

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

    rvcore *m_cpu;
    decoder *m_dec;
    alu *m_alu;
    fpu *m_fpu;
    branch *m_branch;
    load_store *m_ls;
    register_file *m_reg;

    uint64_t npc;
    std::vector<uint32_t> insts;
    uint32_t single_inst[1];

    uint64_t stack_pointer;
};
