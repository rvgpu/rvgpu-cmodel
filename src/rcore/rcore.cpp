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
#include "common/math.hpp"
#include "simt/simt.hpp"

rcore::rcore(simt *simt_processor,vram *rgpu_vram, mmu *rgpu_mmu) {
    m_simt = simt_processor;
    m_vram = rgpu_vram;
    m_mmu = rgpu_mmu;
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
    } else if ((inst_code & VOP1_MASK) == VOP1_MATCH) {
        issued.type = VOP1;
        issued.src0_id = get_bits(inst_code, 0, 9);
        issued.op = get_bits(inst_code, 9, 8);
        issued.dst_id = get_bits(inst_code, 17, 8);
    } else if ((inst_code & VOP2_MASK) == VOP2_MATCH) {
        issued.type = VOP2;
        issued.src0_id = get_bits(inst_code, 0, 9);
        issued.src1_id = get_bits(inst_code, 9, 8);
        issued.dst_id = get_bits(inst_code, 17, 8);
        issued.op = get_bits(inst_code, 25, 6);
    } else if ((inst_code & FLAT_MASK) == FLAT_MATCH) {
        //FLAT类指令长度位64bit
        uint32_t high_word = m_simt->wm->fetch_inst(m_simt->wm->get_pc() + 4);
        issued.type = FLAT;
        issued.op = get_bits(inst_code,18,7);
        issued.src0_id = get_bits(high_word, 0, 8);  //VGPR
        issued.src1_id = get_bits(high_word, 16, 7); //SGPR
        issued.vdata = get_bits(high_word, 8, 8);  //VGPR
        issued.sve = get_bits(high_word, 23, 1);
        issued.dst_id = get_bits(high_word, 24, 8);
        issued.offset = get_bits(inst_code, 0, 13);
        issued.dlc = get_bits(inst_code,13,1);
        issued.glc = get_bits(inst_code,14,1);
        issued.slc = get_bits(inst_code,15,1);
        issued.seg = get_bits(inst_code, 16, 2);
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
        case VOP1: {
            return exe_vop1(issued);
        }
        case VOP2:
            return exe_vop2(issued);
        case FLAT:
            return exe_flat(issued);
        default:
            break;
    }
    return std::make_unique<writeback_t>();
}

std::unique_ptr<writeback_t> rcore::exe_smem(rinst_issue *issued) {
    rwriteback_t res{};
    uint64_t sbase = ((uint64_t) (issued->src0[1]) << 32) | (uint64_t) (issued->src0[0]);
    uint64_t addr = sbase + issued->offset + issued->src1[0];
    res.rid = issued->sdata;

    switch (issued->op) {
        case 0: {   //s_load_b32
            res.data = load(addr, 1);
            res.data_size = 1;
            break;
        }
        case 2: {   //s_load_b128
            res.data = load(addr, 4);
            res.data_size = 4;
            break;
        }
        default:
            break;
    }
    return std::make_unique<rwriteback_t>(res);
}

static bool is_flat_store(uint32_t op) {
    if ((op > 23) && (op < 30)) {
        //GLOBAL_STORE
        return true;
    }
    return false;
}

static uint32_t data_size(rinst_type type, uint32_t op ) {
    switch (type) {
        case FLAT:{
            if (op == 26) {
                return 1;
            }
            break;
        }
        default:
            break;
    }
    return 0;
}

void rcore::get_operand(uint32_t tid, inst_issue *to_issue) {
    auto issued = dynamic_cast<rinst_issue*>(to_issue);
    switch (issued->type) {
        case SMEM: {
            //sbase, is a pair of sgpr
            issued->src0[0] = read_sreg(tid, issued->sbase);
            issued->src0[1] = read_sreg(tid, issued->sbase + 1);
            //soffset
            issued->src1[0] = read_sreg(tid, issued->soffset);
            break;
        }
        case VOP2:
            issued->src1[0] = read_vreg(tid, issued->src1_id);
            [[fallthrough]];
        case VOP1: {
            if (issued->src0_id > 255) {
                issued->src0[0] = read_vreg(tid, issued->src0_id - 256);
            } else {
                issued->src0[0] = read_sreg(tid, issued->src0_id);
            }
            break;
        }
        case FLAT: {
            issued->src0[0] = read_vreg(tid, issued->src0_id);
            issued->src1[0] = read_sreg(tid, issued->src1_id);
            if (issued->src1_id != 0x7c) { // NULL register
                issued->src1[1] = read_sreg(tid, issued->src1_id + 1);
            }
            if (is_flat_store(issued->op)) {
                for(uint32_t i = 0; i < data_size(issued->type, issued->op); i++) {
                    issued->src2[i] = read_vreg(tid, issued->vdata + i);
                }
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

uint32_t rcore::read_vreg(uint32_t wid, uint32_t reg_id) {
    return v_reg[wid][reg_id];
}

void rcore::write_vreg(uint32_t wid, uint32_t reg_id, uint32_t data) {
    v_reg[wid][reg_id] = data;
}

std::vector<uint32_t> rcore::load(uint64_t addr, uint32_t data_size) {
    std::vector<uint32_t> res;
    for(uint32_t len = 0; len < data_size; len++) {
        auto pa = m_mmu->find_pa(addr + sizeof(uint32_t) * len);
        res.push_back(m_vram->read<uint32_t >(pa));
    }
    return res;
}

void rcore::store(uint64_t addr, uint32_t data[], uint32_t data_size) {
    for(uint32_t len = 0; len < data_size; len++) {
        auto pa = m_mmu->find_pa(addr + sizeof(uint32_t) * len);
        m_vram->write<uint32_t>(pa, data[len]);
    }
}

void rcore::write_back(uint32_t tid, writeback_t *data) {
    auto wb_data = dynamic_cast<rwriteback_t*>(data);

    if (wb_data->vreg) {
        for(uint32_t i= 0; i < wb_data->data_size; i++) {
            write_vreg(tid, wb_data->rid + i, wb_data->data[i]);
        }
    } else {
        for(uint32_t i= 0; i < wb_data->data_size; i++) {
            write_sreg(tid, wb_data->rid + i, wb_data->data[i]);
        }
    }
}

std::unique_ptr<writeback_t> rcore::exe_vop1(rinst_issue *issued) {
    rwriteback_t res{};
    switch (issued->op) {
        case 5:  {    //V_CVT_F32_I32
            //fixme: 目前不清楚向量寄存器需要写多少长度的数据，暂时只写1个32位的数据
            res.data_size = 1;
            res.data.push_back(int_to_float((int)(issued->src0[0])));
            res.vreg = true;
            break;
        }
        default:
            break;
    }
    return std::make_unique<rwriteback_t>(res);
}

std::unique_ptr<writeback_t> rcore::exe_vop2(rinst_issue *issued) {
    rwriteback_t res{};
    switch (issued->op) {
        case 8: // V_MUL_F32
            res.data.push_back(fmul(issued->src0[0], issued->src1[0]));
            res.data_size = 1;
            break;
        case 24:  // V_LSHLREV_B32
            res.data.push_back(issued->src1[0] << issued->src0[0]);
            res.data_size = 1;
            break;
        default:
            break;
    }
    return std::make_unique<rwriteback_t>(res);
}

std::unique_ptr<writeback_t> rcore::exe_flat(rinst_issue *issued) {
    rwriteback_t res{};
    uint64_t address = 0;
    if (issued->src1_id != 0x7c) { // 当SGPR不为NULL寄存器时,SGPU提供基地址，VGPR提供32位偏移
        address = ((uint64_t)issued->src1[1] << 32) | (uint64_t)issued->src1[0];
    }
    address += issued->src0[0];

    switch(issued->op) {
        // global_load_b32
        case 20: {
            res.data = load(address, 1);
            res.data_size = 1;
            break;
        }
        case 26: {
            // global_store_b32
            store(address, issued->src2, 1);
            res.data_size = 0; //目前store指令不需要向寄存器中写回数据
            break;
        }
        default:
            break;
    }
    return std::make_unique<rwriteback_t>(res);
}





