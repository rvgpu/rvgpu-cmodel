#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_sw){
    // sw bits: 0x00c52823 # sw  a2, 16(a0)
    uint64_t addr = GetSP();

    exec_instruction(0x00c52823, IN(reg::a2, -333), IN(reg::a0, GetSP()));
    uint32_t result = ReadVRAM<uint32_t>(addr + 16);

    EXPECT_EQ(result, -333);
}