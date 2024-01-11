#pragma once

#include <gtest/gtest.h>

#include "common/regid.hpp"
#include "common/utils.hpp"
#include "simt/simt.hpp"
#include "vram/vram.hpp"
#include "mmu/mmu.hpp"
#include "ut_inst_ref.hpp"
#include "ut_inst_io.hpp"
#include "rvcore/rvcore.hpp"

#define _BITS(bits, pos, width) (((bits) >> (pos)) & ((1ULL << (width)) - 1Ull))

class ut_inst : public ::testing::Test {
protected:
    void SetUp() override {
        m_vram = new vram(1 * 1024 * 1024 * 1024);
        m_mmu = new mmu(m_vram);
        m_dec = new decoder();
        stack_pointer = 0x123;

        // Create page table for the stack, virtual address = 0x123
        PT_BASE = 0x00100000;  // Page table
        PA_BASE = 0x10000000;  // Physical address
        uint64_t level1 = PT_BASE + 0x1000;
        uint64_t level2 = PT_BASE + 0x2000;
        uint64_t level3 = PT_BASE + 0x3000;
        m_mmu->set_page_table_base(PT_BASE);

        m_vram->write<uint64_t>(PT_BASE + 8 * 0, level1);
        m_vram->write<uint64_t>(level1 + 8 * 0, level2);
        m_vram->write<uint64_t>(level2 + 8 * 0, level3);
        m_vram->write<uint64_t>(level3 + 8 * 0, PA_BASE);

        m_cpu = new riskvcore(m_vram, m_mmu);
    }

    void TearDown() override {
        delete m_vram;
        delete m_mmu;
        delete m_cpu;
        stack_pointer = 0;
    }

    template<typename T>
    void WriteVRAM(uint64_t addr, T data) {
        uint64_t pa = PA_BASE + addr;
        m_vram->write<T>(pa, data);
    }

    template<typename T>
    T ReadVRAM(uint64_t addr) {
        uint64_t pa = PA_BASE + addr;
        return m_vram->read<T>(pa);
    }

    uint64_t GetSP() {
        return stack_pointer;
    }

    uint64_t GetInstAddr() {
        return (uint64_t)single_inst;
    }

    //only the thread register can be preloaded;
    void preload_register(special_reg regid, reg_t data) {
        m_cpu->set_sreg(0, regid, data);
    }

    void exec_instruction(uint32_t inst, IN in1, IN in2) {
        // Initialize Instruction and register
        single_inst[0] = inst;
        m_cpu->set_reg(0, static_cast<uint32_t>(in1.first), in1.second);
        m_cpu->set_reg(0, static_cast<uint32_t>(in2.first), in2.second);

        //Decode inst
        inst_issue to_issue = m_dec->decode_inst(inst);
        m_cpu->get_operand(0, to_issue);
        to_issue.currpc = GetInstAddr();
        // Execuate one instruction
        auto res = m_cpu->exe(to_issue, 0);
        m_cpu->write_back(0, res);
        npc = res.pc;
    }

    void test_instruction(uint32_t inst, IN in1, IN in2, IN in3, RES reference) {
        // Initialize Instruction and register
        single_inst[0] = inst;
        m_cpu->set_reg(0, static_cast<uint32_t>(in1.first), in1.second);
        m_cpu->set_reg(0, static_cast<uint32_t>(in2.first), in2.second);
        m_cpu->set_reg(0, static_cast<uint32_t>(in3.first), in3.second);

        //Decode inst
        inst_issue to_issue = m_dec->decode_inst(inst);
        m_cpu->get_operand(0, to_issue);
        to_issue.currpc = GetInstAddr();
        // Execuate one instruction
        auto res = m_cpu->exe(to_issue, 0);
        m_cpu->write_back(0, res);
        npc = res.pc;

        // Check Result
        check_register(reference);
    }
    void test_instruction(uint32_t inst, IN in1, IN in2, RES reference) {
        // Initialize Instruction and register
        single_inst[0] = inst;
        m_cpu->set_reg(0, static_cast<uint32_t>(in1.first), in1.second);
        m_cpu->set_reg(0, static_cast<uint32_t>(in2.first), in2.second);

        //Decode inst
        inst_issue to_issue = m_dec->decode_inst(inst);
        m_cpu->get_operand(0, to_issue);
        to_issue.currpc = GetInstAddr();
        // Execuate one instruction
        auto res = m_cpu->exe(to_issue, 0);
        m_cpu->write_back(0, res);
        npc = res.pc;

        // Check Result
        check_register(reference);
    }
    void test_instruction(uint32_t inst, IN in, RES reference) {
        // Initialize Instruction and register
        single_inst[0] = inst;
        m_cpu->set_reg(0, static_cast<uint32_t>(in.first), in.second);

        //Decode inst
        inst_issue to_issue = m_dec->decode_inst(inst);
        m_cpu->get_operand(0, to_issue);
        to_issue.currpc = GetInstAddr();
        // Execuate one instruction
        auto res = m_cpu->exe(to_issue, 0);
        m_cpu->write_back(0, res);
        npc = res.pc;

        // Check Result
        check_register(reference);
    }
    void test_instruction(uint32_t inst, RES reference) {
        // Initialize Instruction
        single_inst[0] = inst;

        //Decode inst
        inst_issue to_issue = m_dec->decode_inst(inst);
        m_cpu->get_operand(0, to_issue);
        to_issue.currpc = GetInstAddr();
        // Execuate one instruction
        auto res = m_cpu->exe(to_issue, 0);
        m_cpu->write_back(0, res);
        npc = res.pc;

        // Check Result
        check_register(reference);
    }

private:
    vram *m_vram;
    mmu *m_mmu;
    uint64_t PT_BASE;  // Page table
    uint64_t PA_BASE;  // Physical address

    riskvcore *m_cpu;
    decoder *m_dec;
    uint64_t npc;
    uint32_t single_inst[1];
    uint64_t stack_pointer;

    void check_register(RES reference) {
        uint32_t regid = static_cast<uint32_t>(reference.first);
        if (regid <= 31) {
            // Compare to inerger register
            EXPECT_EQ(m_cpu->get_reg(0, regid), reference.second);
        } else if (regid <= 63) {
            // Compare to float register
            EXPECT_DOUBLE_EQ(utils::ul2d(m_cpu->get_reg(0, regid)), utils::ul2d(reference.second));
        } else if (regid == 64){
            // Compare npc
            EXPECT_EQ(npc, reference.second);
        } else {
            printf("error to check regid\n");
            EXPECT_EQ(0, 1);            // here should be failed
        }
    }
};