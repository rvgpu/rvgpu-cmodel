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

/*
 * +-----------------+
 * | cmd_type        |
 * | desc            |  ------------>   command_desc
 * +-----------------+
 * | cmd_type        |
 * | desc            |  ------------>   command_desc
 * +-----------------+
 */

typedef struct {
    uint64_t input;
    uint64_t output;
    uint64_t shader;
} cs_vs_desc;

enum cs_type {
    CS_TYPE_VS = 1,
    CS_TYPE_FS = 2,
    CS_TYPE_END = 3,
};

typedef struct {
    uint32_t vertex_count;
    uint64_t desc;
} command_stream_vs;

typedef struct {
    enum cs_type type;
    union {
        command_stream_vs vs;
    } cmd;
} command_stream;