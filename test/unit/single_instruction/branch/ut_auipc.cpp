#include "ut_inst.hpp"

TEST_F(ut_inst, decode_and_execute_rv64i_auipc) {
    //auipc bits: 0x97; auipc  ra, 0
    test_instruction(0x97, RES(reg::ra, uint64_t(single_inst) + 0));
    test_instruction(0x97, RES(reg::pc, uint64_t(single_inst) + 4));
}