#pragma once

#include "rvcore/alu.hpp"
#include "rvcore/fpu.hpp"
#include "rvcore/load_store.hpp"
#include "rvcore/decoder.hpp"
#include "rvcore/branch.hpp"

class rvcore {
public:
    rvcore(vram *rvcore_vram, mmu *rvcore_mmu) {
        m_dec = new decoder();
        m_alu = new alu(0);
        m_fpu = new fpu(0);
        m_ls = new load_store(rvcore_vram, rvcore_mmu);
        m_branch = new branch();

        m_reg[0] = 0;
    }
    ~rvcore() {
        delete m_dec;
        delete m_alu;
        delete m_fpu;
        delete m_ls;
        delete m_branch;
    }

    void SetReg(uint32_t regid, uint64_t data) {
        if (regid != 0) {
            m_reg[regid] = data;
        }
    }

    void SetSReg(special_reg regid, reg_t data) {
        m_sreg[static_cast<uint32_t>(regid)] = data;
    }

    uint64_t GetReg(uint32_t regid) {
        return m_reg[regid];
    }

    uint64_t execuate(uint64_t pc) {
        writeback_t wb = {};
        uint32_t instcode = 0;
        uint64_t npc = 0;

        // Fetch Instruction
        instcode = *(uint32_t *)pc;
        npc = IS_COMPRESSED_INST(instcode) ? pc + 2 : pc + 4;

        // Decoder
        inst_issue to_issue = m_dec->decode_inst(instcode);
        to_issue.currpc = pc;

        // Register Stage
        register_stage(to_issue);

        // Execuate Instruction
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

        // Writeback
        m_reg[wb.rid] = wb.wdata;

        return npc;
    }

private:
    decoder *m_dec;
    alu *m_alu;
    fpu *m_fpu;
    branch *m_branch;
    load_store *m_ls;

    uint64_t m_reg[64]={};
    reg_t m_sreg[14]={};

    void register_stage(inst_issue &to_issue) {
        to_issue.rs1  = m_reg[to_issue.rs1_id];
        to_issue.rs2  = m_reg[to_issue.rs2_id];
        to_issue.rs3  = m_reg[to_issue.rs3_id];
        to_issue.frs1 = m_reg[to_issue.frs1_id];
        to_issue.frs2 = m_reg[to_issue.frs2_id];
        to_issue.frs3 = m_reg[to_issue.frs3_id];
        to_issue.sreg = m_sreg[static_cast<uint32_t>(to_issue.sreg_id)];
    };
};