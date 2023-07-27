#include <gtest/gtest.h>
#include <vector>

#include "common/configs.h"
#include "top/rvgpu.h"

#define IO_NUM 4
#define SHADER_BINARY_SIZE 0x1000

class Draw : public ::testing::Test {
protected:
    void SetUp() override {
        gpu = new rvgpu();
    }

    void TearDown() override {
    }


    void vertex_command(uint32_t vcount, uint64_t binary, uint64_t layout) {
        rvgpu_command_vs vs = {};
        vs.vertex_count = vcount;
        vs.shader = binary;
        vs.layout = layout;
        commands.push_back(rvgpu_command {.type = RVGPU_COMMAND_TYPE_VS, .cmd = {vs}});
    }

    void end_command() {
        commands.push_back(rvgpu_command {.type = RVGPU_COMMAND_TYPE_END, .cmd = {}});
    }

    void run() {
        gpu->run((uint64_t)commands.data());
    }

    void load_shader(const char *fname, uint32_t *binary) {

    }

private:
    rvgpu *gpu;
    std::vector<rvgpu_command> commands;
};

class Shader {
public:
    struct shaderlayout {
        uint64_t io[IO_NUM];
    };

    Shader() {
        layout = (struct shaderlayout *)malloc(sizeof(struct shaderlayout));
        binary = (uint32_t *)malloc(SHADER_BINARY_SIZE * 4);
    }

    void SetupIO(int index, uint64_t ptr) {
        layout->io[index] = ptr;
    }

    void SetupShaderBinary(uint64_t shaderbin) {
        binary = (uint32_t *)shaderbin;
    }

    void SetupShaderBinary(const char *fname) {
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

    struct shaderlayout *layout;
    uint32_t *binary;
};
