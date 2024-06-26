#pragma once

#include "top/command_stream.h"
#include "common/type.hpp"
#include <memory>
class mcore {
public:
    virtual void register_setup(message msg) =0;
    virtual std::unique_ptr<inst_issue> decode(uint32_t inst_code) = 0;
    virtual void get_operand(uint32_t tid, inst_issue* to_issue) = 0;
    virtual std::unique_ptr<writeback_t> exe(inst_issue* to_issue, uint32_t tid) = 0;
    virtual void write_back(uint32_t tid, writeback_t* data) = 0;
};