#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <elf.h>

#include "common/configs.h"
#include "top/rvgpu.h"

#define IO_NUM 4
#define SHADER_BINARY_SIZE 0x1000
#define STACK_POINT_SIZE 0x4000

class GPUExecuator : public ::testing::Test {
protected:
    void SetUp() override {
        stack_pointer = (uint64_t)malloc(STACK_POINT_SIZE * 128 + 0x1000);
        stack_pointer += 0x1000;
        gpu = new rvgpu();
    }

    void TearDown() override {
    }


    void end_command() {

    }

    void run1d (uint32_t count) {
        rvgpu_command cmd;
        cmd.type = RVGPU_COMMAND_TYPE_1D;
        cmd.range = {.x= count, .y = 0, .z = 0};
        cmd.shader.pointer = pc;
        cmd.shader.stack_pointer = stack_pointer;
        cmd.shader.argsize = params.size();
        for (uint32_t i=0; i<params.size(); i++) {
            cmd.shader.args[i] = params[i];
        }

        commands.push_back(std::move(cmd));

        gpu->run((uint64_t)commands.data());
    }


    void PushParam(uint64_t data) {
        params.push_back(data);
    }

    void LoadELF(const char *fname) {
        std::string fpath;
        fpath += PROJECT_TEST_DRAW_SHADER_DATA_PATH;
        fpath += "/";
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

        Loader();
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
    void Loader() {
        Elf64_Ehdr *header = (Elf64_Ehdr *)elf_binary;
        if(CheckELF(header) == false) {
            std::cout << "Error to check elf file" << std::endl;
            return ;
        }

        Elf64_Phdr *phdr = (Elf64_Phdr *)((uint64_t)elf_binary + header->e_phoff);
        for (uint32_t i=0; i<header->e_phnum; i++) {
            if (phdr[i].p_type == 1) {
                uint64_t baddr = (uint64_t)elf_binary + phdr[i].p_offset;
                uint64_t maddr = (uint64_t)instmem + phdr[i].p_paddr;
                memcpy((void *)maddr, (void *)baddr, phdr[i].p_memsz);
            }
        }

        pc = (uint64_t)instmem + header->e_entry;
    }

    char *elf_binary;
    uint64_t pc;
    std::vector<uint64_t> params;

    rvgpu *gpu;
    std::vector<rvgpu_command> commands;
    uint64_t stack_pointer;
    uint32_t instmem[0x20000];
};
