#include "sm/decoder.h"
#include "instructions/encoding.h"
#include "sm/compute_unit.h"

reg_t rv32i_addi(compute_unit *p, insn_t insn, reg_t pc)
{
  #define xlen 32
  reg_t npc = sext_xlen(pc + insn_length( MATCH_ADDI));
  #include "instructions/addi.h"
  //trace_opcode(p,  MATCH_ADDI, insn);
  #undef xlen
  return npc;
}
