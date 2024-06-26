#include <bitset>
#include "alu.hpp"
#include "fpu.hpp"
#include "load_store.hpp"
#include "decoder.hpp"
#include "register_file.hpp"
#include "simt/core.hpp"
#include "top/command_stream.h"
#include "branch.hpp"


class riscvcore : public mcore {
public:
    riscvcore(vram *rvgpu_vram, mmu *rvgpu_mmu);
    ~riscvcore();
    std::unique_ptr<writeback_t> exe(inst_issue* to_issue, uint32_t tid) override;
    std::unique_ptr<inst_issue> decode(uint32_t inst_code) override;
    void register_setup(message msg) override;
    void get_operand(uint32_t tid, inst_issue* to_issue) override;
    void write_back(uint32_t tid, writeback_t* data) override;
    void set_reg(uint32_t tid, uint32_t regid, reg_t data);
    reg_t get_reg(uint32_t tid, uint32_t regid);
    void set_sreg(uint32_t tid, special_reg regid, reg_t data);

private:
    alu             *m_alu[WARP_THREAD_N];
    fpu             *m_fpu[WARP_THREAD_N];
    register_file   *m_reg;
    load_store      *m_ls;
    branch          *m_branch;
    decoder         *m_decoder;
    uint64_t        pc;
};