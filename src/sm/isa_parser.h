#ifndef RVGSIM_ISA_PARSER_H
#define RVGSIM_ISA_PARSER_H

#include <string>

static std::string strtolower(const char* str) {
    std::string res;
    for (const char *r = str; *r; r++)
        res += std::tolower(*r);
    return res;
}
class isa_parser_t {
public:
    explicit isa_parser_t(const char* str) {
        isa_string = strtolower(str);
        if (isa_string.compare(0,4,"rv32") == 0) {
            max_xlen = 32;
        }else if (isa_string.compare(0,4,"rv64") == 0) {
            max_xlen = 64;
        }else {
            printf("ISA strings must begin with RV32 or RV64");
        }
    }

    uint32_t get_max_xlen() const {
        return max_xlen;
    }
private:
    uint32_t max_xlen;
    std::string isa_string;
};
#endif //RVGSIM_ISA_PARSER_H
