#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sh){
    // 0x00a11823       sh  a0, 16(sp)
    uint64_t addr = GetSP();
    WriteVRAM<uint32_t>(addr + 16, 0xaaaaaaaa);

    exec_instruction(0x00a11823, IN(reg::a0, 0x12345678), IN(reg::sp, GetSP()));
    uint32_t result = ReadVRAM<uint32_t>(addr + 16);

    EXPECT_EQ(result, 0xaaaa5678);
}