#include "rvcore.hpp"
#include "top/command_stream.h"

riskvcore::riskvcore(vram *rvgpu_vram, mmu *rvgpu_mmu) {
    m_reg = new register_file();
    m_ls = new load_store(rvgpu_vram, rvgpu_mmu);
    m_decoder = new decoder();

    for (uint32_t i=0; i<WARP_THREAD_N; i++) {
        m_alu[i] = new alu(i);
        m_fpu[i] = new fpu(i);
    }
}
riskvcore::~riskvcore() {
    delete m_reg;
    delete m_ls;
    delete m_decoder;

    for (uint32_t i=0; i<WARP_THREAD_N; i++) {
        delete m_alu[i];
        delete m_fpu[i];
    }
}

writeback_t riskvcore::exe(inst_issue* issue, uint32_t tid) {
    auto to_issue = dynamic_cast<rvinst_issue*>(issue);
    writeback_t wb = {};
    bool is_compressed = IS_COMPRESSED_INST(to_issue->bits);
    uint64_t pc_inc = 0;
    switch (to_issue->type) {
        case encoding::INST_TYPE_ALU: {
            wb = m_alu[tid]->run(*to_issue);
            break;
        }
        case encoding::INST_TYPE_FPU: {
            wb = m_fpu[tid]->run(*to_issue);
            break;
        }
        case encoding::INST_TYPE_LS: {
            wb = m_ls->run(*to_issue);
            break;
        }
        case encoding::INST_TYPE_BRANCH: {
            wb = m_branch->run(*to_issue, pc_inc);
            break;
        }
        case encoding::INST_TYPE_NOP: {
            break;
        }
        default:
            RVGPU_ERROR_PRINT("Instruction ERROR: %x\n", to_issue->bits);
            break;
    }

    if(pc_inc) {
        wb.pc = to_issue->currpc + pc_inc;
    }else {
        wb.pc = to_issue->currpc + (is_compressed ? 2: 4);
    }
    return wb;
}

void riskvcore::register_setup(message msg) {
    for (uint32_t i=0; i<WARP_THREAD_N; i++) {
        if (i < msg.count) {
            m_reg->write(i, uint64_t(reg::s0), 0);
            m_reg->write(i, uint64_t(reg::ra), 0);
            m_reg->sreg_write(i, special_reg::t0, msg.start + i);

            RVGPU_DEBUG_PRINT("[SP][WARP0.%d] setup sp: 0x%lx\n", i, msg.shader.stack_pointer + 0x1000 * i);
            m_reg->write(i, uint64_t(reg::sp), msg.shader.stack_pointer + 0x1000 * i);

            for (uint32_t argi=0; argi<msg.shader.argsize; argi++) {
                RVGPU_DEBUG_PRINT("[SP][WARP0.%d] setup a%d(arg[%d]): 0x%lx\n", i, argi, argi, msg.shader.args[argi]);
                m_reg->write(i, uint64_t(reg::a0) + argi, msg.shader.args[argi]);
            }
        }
    }
}

void riskvcore::get_operand(uint32_t tid, inst_issue* issue) {
    auto to_issue = dynamic_cast<rvinst_issue*>(issue);
    to_issue->rs1 = m_reg->read(tid, to_issue->rs1_id);
    to_issue->rs2 = m_reg->read(tid, to_issue->rs2_id);
    to_issue->rs3 = m_reg->read(tid, to_issue->rs3_id);
    to_issue->frs1 = m_reg->read(tid, to_issue->frs1_id);
    to_issue->frs2 = m_reg->read(tid, to_issue->frs2_id);
    to_issue->frs3 = m_reg->read(tid, to_issue->frs3_id);
    to_issue->sreg = m_reg->sreg_read(tid, to_issue->sreg_id);
}

void riskvcore::write_back(uint32_t tid, writeback_t data) {
    m_reg->write(tid, data.rid, data.wdata);
}

void riskvcore::set_reg(uint32_t tid, uint32_t regid, uint64_t data) {
    if(regid != 0)
        m_reg->write(tid, regid, data);
}

reg_t riskvcore::get_reg(uint32_t tid, uint32_t regid) {
    return m_reg->read(tid, regid);
}

//write special register
void riskvcore::set_sreg(uint32_t tid, special_reg regid, reg_t data) {
    m_reg->sreg_write(tid,regid,data);
}

std::unique_ptr<inst_issue> riskvcore::decode(uint32_t inst_code) {
    auto res = m_decoder->decode_inst(inst_code);
    return std::make_unique<rvinst_issue>(res);
}
