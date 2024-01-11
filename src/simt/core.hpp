#pragma once

#include "top/command_stream.h"

class mcore {
public:
    virtual void register_setup(message msg) =0;
    virtual void get_operand(uint32_t tid, inst_issue &to_issue) = 0;
    virtual writeback_t exe(inst_issue to_issue, uint32_t tid) = 0;
    virtual void write_back(uint32_t tid, writeback_t data) = 0;
};