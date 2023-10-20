#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sb){
    // 0x00a58023       sb  a0, 0(a1)
    uint64_t addr = GetSP();
    WriteVRAM<uint32_t>(addr, 0xaaaaaaaa);

    exec_instruction(0x00a58023, IN(reg::a0, 0x12345678), IN(reg::a1, GetSP()));
    uint32_t result = ReadVRAM<uint32_t>(addr);

    EXPECT_EQ(result, 0xaaaaaa78);
}