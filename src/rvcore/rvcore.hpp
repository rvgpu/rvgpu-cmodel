#include <bitset>
#include "alu.hpp"
#include "fpu.hpp"
#include "load_store.hpp"
#include "decoder.hpp"
#include "register_file.hpp"
#include "simt/core.hpp"
#include "top/command_stream.h"


class riskvcore : public mcore {
public:
    riskvcore(vram *rvgpu_vram, mmu *rvgpu_mmu);
    ~riskvcore();
    void exe(inst_issue to_issue, uint32_t tid) override;

    void register_setup(message msg) override;
    void get_operand(uint32_t tid, inst_issue &to_issue) override;
    void write_back(uint32_t tid, writeback_t data) override;
private:
        
    alu             *m_alu[WARP_THREAD_N];
    fpu             *m_fpu[WARP_THREAD_N];
    register_file   *m_reg;
    load_store      *m_ls;
    uint64_t        pc;
};