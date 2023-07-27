#include <gtest/gtest.h>
#include <vector>

#include "common/configs.h"
#include "top/rvgpu.h"

#define SHADER_BINARY_SIZE 0x1000

class Draw : public ::testing::Test {
protected:
    void SetUp() override {
        gpu = new rvgpu();
    }

    void TearDown() override {
    }

    void vertex_command(uint64_t binary, command_stream_vs cs_vs) {
        commands.push_back(command_stream {.type = CS_TYPE_VS, .shader = (uint64_t)binary, .cmd = {cs_vs}});
    }

    void end_command() {
        commands.push_back(command_stream {.type = CS_TYPE_END, .cmd = {}});
    }

    void run() {
        gpu->run((uint64_t)commands.data());
    }

    void load_shader(const char *fname, uint32_t *binary) {
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

private:
    rvgpu *gpu;
    std::vector<command_stream> commands;
};
