/*
 * Copyright © 2023 Sietium Semiconductor.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#pragma once

#include  <stdint.h>

typedef enum {
    RVGPU_COMMAND_TYPE_1D = 1,
    RVGPU_COMMAND_TYPE_2D,
    RVGPU_COMMAND_TYPE_END,
} rvgpu_command_type;

typedef struct {
    uint64_t pointer;
    uint64_t stack_pointer;
    uint32_t argsize;
    uint64_t args[8];
} program_t;

typedef struct {
    rvgpu_command_type type;
    program_t shader;

    struct {
        uint32_t x;
        uint32_t y;
        uint32_t z;
    } range;
} rvgpu_command;

typedef struct {
    uint32_t target;
    uint32_t start;
    uint32_t count;
    program_t shader;
} message;