#include <cstdio>
#include <vector>

#include "common/configs.h"

void read_asm_file(const char *fname, uint32_t *binary) {
    std::string fpath;
    fpath += PROJECT_TEST_DRAW_SHADER_DATA_PATH;
    fpath += "/";
    fpath += fname;
    FILE *fp = fopen(fpath.c_str(), "r");
    char line[200];

    uint32_t addr;
    uint32_t b0, b1, b2, b3;
    while (fgets(line, 200, fp)) {
        sscanf(line, "%x: %x %x %x %x", &addr, &b0, &b1, &b2, &b3);
        uint32_t data = ((b0 & 0xff) << 0) |
                        ((b1 & 0xff) << 8) |
                        ((b2 & 0xff) << 16) |
                        ((b3 & 0xff) << 24);
        binary[addr/4] = data;
        // printf("%x: %08x\n", addr, data);
    }
}