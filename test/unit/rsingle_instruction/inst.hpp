#ifndef RVGSIM_INST_HPP
#define RVGSIM_INST_HPP

#include <gtest/gtest.h>
#include "rcore/rcore.hpp"

class inst : public ::testing::Test {
public:
    std::shared_ptr<inst_issue> decode() {
        if(!read<uint32_t >(m_pc)) {
            printf("must init instructions first \n" );
            return std::make_unique<inst_issue>();
        }
        wm_init();
        return m_core->decode(m_simt->wm->fetch_inst(m_simt->wm->get_pc()));
    }

    void inst_init(uint32_t insts) {
        write(m_pc, insts);
    }
    void inst_init(uint32_t low, uint32_t high) {
        write(m_pc, low);
        write(m_pc + 4, high);
    }

    std::shared_ptr<writeback_t> exe(rinst_issue* issued) {
        return m_core->exe(issued, 0);

    }
    void preload_data_to_vram(uint64_t addr, std::vector<uint32_t> data, uint32_t data_size) {
        for (uint32_t i = 0; i < data_size; i++) {
            write(addr + i * sizeof (uint32_t), data[i]);
        }
    }

private:
    void wm_init() {
        program_t shader;
        shader.pointer = m_pc;
        message msg{.target = 0, .start = 0, .count = 0, .shader = shader};
        m_simt->wm->setup(msg);
    }

    template<class T> T read(uint64_t va) {
        return m_vram->read<uint32_t>(m_mmu->find_pa(va));
    }

    template<class T> void write(uint64_t va, T data) {
        m_vram->write(m_mmu->find_pa(va), data);
    }
protected:
    void SetUp() override {
        m_vram = new vram(1 * 1024 * 1024 * 1024);
        m_mmu = new mmu(m_vram);
        m_simt = new simt(m_vram, m_mmu);
        m_core = new rcore(m_simt, m_vram, m_mmu);

        // Create page table for virtual address = 0x123
        uint64_t PT_BASE = 0x00100000;  // Page table
        uint64_t PA_BASE = 0x10000000;  // Physical address
        uint64_t level1 = PT_BASE + 0x1000;
        uint64_t level2 = PT_BASE + 0x2000;
        uint64_t level3 = PT_BASE + 0x3000;
        m_mmu->set_page_table_base(PT_BASE);

        m_vram->write<uint64_t>(PT_BASE, level1);
        m_vram->write<uint64_t>(level1, level2);
        m_vram->write<uint64_t>(level2, level3);
        m_vram->write<uint64_t>(level3, PA_BASE);
    }
    void TearDown() override {
        delete m_vram;
        delete m_mmu;
        delete m_simt;
        delete m_core;
    }

private:
    vram *m_vram;
    mmu *m_mmu;
    rcore *m_core;
    simt *m_simt;

    uint64_t m_pc = 0x123;
};
#endif //RVGSIM_INST_HPP
