#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <elf.h>

#include "top/command_stream.h"
#include "common/configs.h"
#include "top/rvgpu.h"

class GPUExecuator_with_vram : public ::testing::Test {
protected:
    void SetUp() override {
        stack_pointer = (uint64_t)malloc(SM_STACK_SIZE * SM_NUM + 0x1000);
        stack_pointer += 0x1000;
        gpu_malloc_addr = 0;

        gpu = new rvgpu();
    }

    void TearDown() override {
    }

    uint64_t gpu_malloc(uint32_t size) {
        uint64_t addr = gpu_malloc_addr;
        gpu_malloc_addr += size;
        return addr;
    }

    void gpu_write_vram(uint64_t addr, uint64_t data, uint32_t size) {
        gpu->write_vram(addr, data, size);
    }

    uint64_t gpu_read_vram(uint64_t addr, uint32_t size) {
        return gpu->read_vram(addr, size);
    }

    void gpu_write_register(uint64_t addr, uint32_t data) {
        gpu->write_register(addr, data);
    }

    uint32_t gpu_read_register(uint64_t addr) {
        return gpu->read_register(addr);
    }

    void gpu_memcpy(uint64_t dest_addr, uint64_t src_addr, uint32_t size, bool host_to_device) {
        if (host_to_device) {            
            uint8_t *addr = (uint8_t *)src_addr;
            for (uint32_t i = 0; i < size; i++) {
                gpu->write_vram(dest_addr + i, addr[i], 1);
            }
        } else {
            uint8_t *addr = (uint8_t *)dest_addr;
            for (uint32_t i = 0; i < size; i++) {
                addr[i] = gpu->read_vram(src_addr + i, 1);
            }
        }        
    }

    uint64_t gpu_get_vram_addr() {
        return gpu->get_vram_addr();
    }

    void run1d_with_vram(uint32_t count, uint64_t params_addr, uint32_t params_size) {
        rvgpu_command cmd;
        cmd.type = RVGPU_COMMAND_TYPE_1D;
        cmd.range = {.x= count, .y = 0, .z = 0};

        cmd.shader.pointer = pc;
        cmd.shader.stack_pointer = stack_pointer;

        cmd.shader.argsize = params_size;
        for (uint32_t i=0; i<params_size; i++) {
            cmd.shader.args[i] = gpu->read_vram(params_addr + i * 8, 8);
        }

        commands.push_back(std::move(cmd));
        gpu->run((uint64_t)commands.data());

        commands.clear();
    }

    void run2d_with_vram(uint32_t x, uint32_t y, uint64_t params_addr, uint32_t params_size) {
        rvgpu_command cmd;
        cmd.type = RVGPU_COMMAND_TYPE_2D;
        cmd.range = {.x= x, .y = y, .z = 0};

        cmd.shader.pointer = pc;
        cmd.shader.stack_pointer = stack_pointer;

        cmd.shader.argsize = params_size;
        uint64_t *addr = (uint64_t *)params_addr;
        for (uint32_t i=0; i<params_size; i++) {
            cmd.shader.args[i] = gpu->read_vram(params_addr + i * 8, 8);
        }

        commands.push_back(std::move(cmd));
        gpu->run((uint64_t)commands.data());

        commands.clear();
    }

    void PushParam_with_vram(uint64_t params_addr, uint32_t id, uint64_t data) {
        gpu->write_vram(params_addr + id * 8, data, 8);
    }

    void LoadELF_with_vram(uint64_t shader_addr, const char *testname, const char *fname) {
        std::string fpath;
        fpath += PROJECT_TEST_DRAW_BINARY_PATH;
        fpath += "/";
        fpath += testname;
        fpath += "/data/";
        fpath += fname;

        std::filebuf *fbuf;
        std::ifstream filestr;

        filestr.open(fpath.c_str(), std::ios::binary);
        fbuf = filestr.rdbuf();
        long size = fbuf->pubseekoff(0, std::ios::end, std::ios::in);
        fbuf->pubseekpos(0, std::ios::in);

        elf_binary = new char[size];
        fbuf->sgetn(elf_binary, size);
        filestr.close();

        Loader_with_vram(shader_addr);
    }

    void WritePPM(const char *fname, uint32_t w, uint32_t h, unsigned char *fb) {
        std::string fpath;
        fpath += fname;
        fpath += ".ppm";
        FILE *wf = fopen(fpath.c_str(), "w");
        fprintf(wf, "P3\n");
        fprintf(wf, "%u %u\n", w, h);
        fprintf(wf, "255\n");
        for (uint32_t i=0; i<h; i++) {
            for (uint32_t j=0; j<w; j++) {
                uint32_t index = i * w + j;
                uint8_t r = fb[index * 4 + 0];
                uint8_t g = fb[index * 4 + 1];
                uint8_t b = fb[index * 4 + 2];
                // uint8_t a = testfb[index + 0];
                fprintf(wf, "%d %d %d\n", r, g, b);
            }
        }

        fclose(wf);
    }
private:
    bool CheckELF(Elf64_Ehdr *header) {
        // 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
        if (header->e_ident[0] != 0x7f) {
            return false;
        }
        if (header->e_ident[1] != 0x45) {
            return false;
        }
        if (header->e_ident[2] != 0x4c) {
            return false;
        }
        if (header->e_ident[3] != 0x46) {
            return false;
        }
        if (header->e_ident[4] != 0x02) {
            return false;
        }
        if (header->e_ident[5] != 0x01) {
            return false;
        }
        if (header->e_ident[6] != 0x01) {
            return false;
        }

        return true;
    }
    void Loader_with_vram(uint64_t shader_addr) {
        Elf64_Ehdr *header = (Elf64_Ehdr *)elf_binary;
        if(CheckELF(header) == false) {
            std::cout << "Error to check elf file" << std::endl;
            return ;
        }

        Elf64_Phdr *phdr = (Elf64_Phdr *)((uint64_t)elf_binary + header->e_phoff);

        for (uint32_t i=0; i<header->e_phnum; i++) {
            if (phdr[i].p_type == 1) {
                uint64_t baddr = (uint64_t)elf_binary + phdr[i].p_offset;
                uint64_t maddr = (uint64_t)shader_addr + phdr[i].p_paddr;
                gpu_memcpy(maddr, baddr, phdr[i].p_memsz, true);
            }
        }

        pc = ((uint64_t)shader_addr + gpu_get_vram_addr()) + header->e_entry;
    }

    char *elf_binary;
    rvgpu *gpu;
    uint64_t pc;
    uint64_t stack_pointer;
    uint64_t gpu_malloc_addr;
    std::vector<rvgpu_command> commands;
};
