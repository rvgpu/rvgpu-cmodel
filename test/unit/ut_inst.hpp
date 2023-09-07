#include <gtest/gtest.h>

#include "simt/simt.hpp"
#include "common/regid.hpp"

#define STACK_SIZE  2000

class ut_inst : public ::testing::Test {
protected:
    void SetUp() override {
        stack_pointer = (uint64_t)malloc(0x2000);
        stack_pointer += 0x1000;

        m_dec = new dec();
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

    dec *m_dec;
    alu *m_alu;
    fpu *m_fpu;
    branch *m_branch;
    load_store *m_ls;
    register_file *m_reg;

    uint64_t npc;
    std::vector<uint32_t> insts;

    uint64_t stack_pointer;
};
