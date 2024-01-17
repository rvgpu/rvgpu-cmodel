/*
 * Copyright © 2023 Sietium Semiconductor.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "rcore.hpp"
#include "common/type.hpp"
#include "simt/simt.hpp"

rcore::rcore(simt *simt_processor,vram *rgpu_vram, mmu *rgpu_mmu) {
    m_simt = simt_processor;
    m_vram = rgpu_vram;
    m_mmu = rgpu_mmu;
    for (auto tid = 0; tid < SP_WARP_N;) {

    }
}

static uint32_t get_bits(uint32_t inst, uint32_t lsb, uint32_t len) {
    return ((inst >> lsb) & ((uint32_t(1) << len) - 1));
}
std::unique_ptr<inst_issue> rcore::decode(uint32_t inst_code) {
    rinst_issue issued {};
    if ((inst_code & SOPP_MASK) == SOPP_MATCH) {
        issued.op = get_bits(inst_code, 16, 7);
        issued.simm16 = get_bits(inst_code,0,16);
        issued.type = SOPP;
    } else if ((inst_code & SMEM_MASK) == SMEM_MATCH) {
        //SMEM类指令长度位64bit
        uint32_t high_word = m_simt->wm->fetch_inst(m_simt->wm->get_pc() + 4);
        issued.op = get_bits(inst_code, 18, 8);
        issued.sbase = get_bits(inst_code, 0, 6);
        issued.sdata = get_bits(inst_code, 6, 7);
        issued.dlc = get_bits(inst_code, 14, 1);
        issued.glc = get_bits(inst_code, 16, 1);
        issued.offset = get_bits(high_word, 0, 21);
        issued.soffset = get_bits(high_word, 25, 7);
        issued.type = SMEM;
    }

    if (issued.type == UNKNOWN) {
        printf("decode error ! \n");
    }
    return std::make_unique<rinst_issue>(issued);
}

std::unique_ptr<writeback_t> rcore::exe(inst_issue *to_issue, uint32_t tid) {
    auto issued = dynamic_cast<rinst_issue*>(to_issue);
    switch (issued->type) {
        case SOPP:
            break;
        case SMEM: {
            return exe_smem(issued);
        }
        default:
            break;
    }
    return std::make_unique<writeback_t>();
}

std::unique_ptr<writeback_t> rcore::exe_smem(rinst_issue *issued) {
    rwriteback_t res{};
    switch (issued->op) {
        case 2: {   //s_load_b128
            uint64_t sbase = ((uint64_t) (issued->src0[1]) << 32) | (uint64_t) (issued->src0[0]);
            uint64_t addr = sbase + issued->offset + issued->src1[0];
            res.data = load(addr, 4);
            res.rid = issued->sdata;
            res.data_size = 4;
            break;
        }
        default:
            break;
    }
    return std::make_unique<rwriteback_t>(res);
}

void rcore::get_operand(uint32_t tid, inst_issue *to_issue) {
    auto issued = dynamic_cast<rinst_issue*>(to_issue);
    switch (issued->type) {
        case SMEM: {
            switch (issued->op) {
                case 2: //s_load_b128
                    //sbase, is a pair of sgpr
                    issued->src0[0] = read_sreg(tid, issued->sbase);
                    issued->src0[1] = read_sreg(tid, issued->sbase + 1);
                    //soffset
                    issued->src1[0] = read_sreg(tid, issued->soffset);
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}

uint32_t rcore::read_sreg(uint32_t tid, uint32_t reg_id) {
    return s_reg[tid][reg_id];
}

void rcore::write_sreg(uint32_t tid, uint32_t reg_id, uint32_t data) {
    s_reg[tid][reg_id] = data;
}

std::vector<uint32_t> rcore::load(uint64_t addr, uint32_t data_size) {
    std::vector<uint32_t> res;
    auto pa = m_mmu->find_pa(addr);
    for(uint32_t len = 0; len < data_size; len++) {
        res.push_back(m_vram->read<uint32_t >(pa + sizeof(uint32_t)*len));
    }
    return res;
}

void rcore::write_back(uint32_t tid, writeback_t *data) {
    auto wb_data = dynamic_cast<rwriteback_t*>(data);

    for(uint32_t i= 0; i < wb_data->data_size; i++) {
        write_sreg(tid, wb_data->rid + i, wb_data->data[i]);
    }
}



