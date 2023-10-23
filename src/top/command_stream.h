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

#define PACKED __attribute__((aligned(8)))

typedef PACKED struct {
    uint64_t        pointer:64;
    uint64_t        stack_pointer:64;
    uint64_t        argsize:64;
    uint64_t        args[8];
} program_t;

typedef PACKED struct {
    uint64_t        x:32;
    uint64_t        y:32;
    uint64_t        z:32;
    uint64_t        res:32;
} dimension_t;

typedef PACKED struct {
    dimension_t     dim;
    program_t       program;
} rvgpu_command;

typedef struct {
    uint32_t target;
    uint32_t start;
    uint32_t count;
    program_t shader;
} message;