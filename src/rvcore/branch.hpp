#pragma once

#include "inst_issue.hpp"

class branch {
public:
    branch();

    writeback_t run(inst_issue to_issue, uint64_t &pc_increment);
};