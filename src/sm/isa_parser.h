#ifndef RVGSIM_ISA_PARSER_H
#define RVGSIM_ISA_PARSER_H

#include <bitset>
#include <string>

typedef enum {
  // 65('A') ~ 90('Z') is reserved for standard isa in misa
  EXT_ZFH = 'Z' + 1,
  EXT_ZFHMIN,
  EXT_ZBA,
  EXT_ZBB,
  EXT_ZBC,
  EXT_ZBS,
  EXT_ZBKB,
  EXT_ZBKC,
  EXT_ZBKX,
  EXT_ZCA,
  EXT_ZCB,
  EXT_ZCD,
  EXT_ZCF,
  EXT_ZCMP,
  EXT_ZCMT,
  EXT_ZKND,
  EXT_ZKNE,
  EXT_ZKNH,
  EXT_ZKSED,
  EXT_ZKSH,
  EXT_ZKR,
  EXT_ZMMUL,
  EXT_ZBPBO,
  EXT_ZPN,
  EXT_ZPSFOPERAND,
  EXT_ZVFH,
  EXT_ZVFHMIN,
  EXT_SMEPMP,
  EXT_SMSTATEEN,
  EXT_SMRNMI,
  EXT_SSCOFPMF,
  EXT_SVADU,
  EXT_SVNAPOT,
  EXT_SVPBMT,
  EXT_SVINVAL,
  EXT_ZDINX,
  EXT_ZFA,
  EXT_ZFBFMIN,
  EXT_ZFINX,
  EXT_ZHINX,
  EXT_ZHINXMIN,
  EXT_ZICBOM,
  EXT_ZICBOZ,
  EXT_ZICNTR,
  EXT_ZICOND,
  EXT_ZIHPM,
  EXT_ZVBB,
  EXT_ZVBC,
  EXT_ZVFBFMIN,
  EXT_ZVFBFWMA,
  EXT_ZVKG,
  EXT_ZVKNED,
  EXT_ZVKNHA,
  EXT_ZVKNHB,
  EXT_ZVKSED,
  EXT_ZVKSH,
  EXT_XZBP,
  EXT_XZBS,
  EXT_XZBE,
  EXT_XZBF,
  EXT_XZBC,
  EXT_XZBM,
  EXT_XZBR,
  EXT_XZBT,
  EXT_SSTC,
  EXT_ZACAS,
  EXT_INTERNAL_ZFH_MOVE,
  NUM_ISA_EXTENSIONS
} isa_extension_t;

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
        } else if (isa_string.compare(0,4,"rv64") == 0) {
            max_xlen = 64;
        } else {
            printf("ISA strings must begin with RV32 or RV64");
        }

        extension_table['I'] = true;

        const char* isa_str = isa_string.c_str();  
        auto p = isa_str;

        for (p += 5; islower(*p); ++p) {
            extension_table[toupper(*p)] = true;
        }
    }

    uint32_t get_max_xlen() const {
        return max_xlen;
    }

    bool extension_enabled(unsigned char ext) const {
        return extension_enabled(isa_extension_t(ext));
    }
    bool extension_enabled(isa_extension_t ext) const {
        return extension_table[ext];
    }
private:
    uint32_t max_xlen;
    std::string isa_string;
    std::bitset<NUM_ISA_EXTENSIONS> extension_table;
};
#endif //RVGSIM_ISA_PARSER_H
