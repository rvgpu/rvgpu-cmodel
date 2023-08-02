#include <gtest/gtest.h>

#include "top/rvgpu.h"
#include "common/command_stream.h"

#include "draw.hpp"

struct viewport {
    float x;
    float y;
    float w;
    float h;
};

typedef struct {
    unsigned long vp;
    unsigned long out_position;
    unsigned long out_color;
} vs_io;

typedef struct {
    unsigned long in_position;
    unsigned long in_color;
    unsigned long out_color;
} fs_io;

TEST_F(Draw, triangle) {
    Shader vshader;
    Shader fshader;
    int32_t count = 3;

    struct viewport *my_vp = (struct viewport *) malloc(sizeof(struct viewport));
    my_vp->x = 0.0f;
    my_vp->y = 0.0f;
    my_vp->w = 400.0f;
    my_vp->h = 300.0f;

    float *my_position = (float *) malloc(count * 7 * sizeof(float));
    float *my_color = (float *) malloc(count * 7 * sizeof(float));

    vs_io *vsio = (vs_io *) malloc(sizeof(vs_io));
    vsio->vp = reinterpret_cast<unsigned long>(my_vp);
    vsio->out_position = reinterpret_cast<unsigned long>(my_position);
    vsio->out_color = reinterpret_cast<unsigned long>(my_color);

    vshader.SetupShaderBinary("vertex_shader_vt14.vs");
    vertex_command(count, (uint64_t)vshader.binary, (uint64_t)vsio);

    // VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
    fs_io *fsio = (fs_io *) malloc(sizeof(fs_io));
    fsio->in_position = vsio->out_position;
    fsio->in_color = vsio->out_color;
    fshader.SetupShaderBinary("fragment_shader_vt14.vs");
    fragment_command(count, 3, (uint64_t)NULL, (uint64_t)fsio);

    end_command();

    run();

    // Test
    float position[3][2] = {
        {-0.5, 0.5},
        {0.5, 0.5},
        {0, -0.5}
    };

    float colors[3][3] = {
        {0.0, 0.0, 1.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
    };

    float fx, fy, fz, fw, fr, fg, fb;
    int i;

    for (i = 0; i < count; i++) {
        fx = position[i][0];
        fy = position[i][1];
        fz = 0.0f;
        fw = 1.0f;
        fr = colors[i][0];
        fg = colors[i][1];
        fb = colors[i][2];

        fx = my_vp->x + fx * (my_vp->w);
        fy = my_vp->y + fy * (my_vp->h);

        float *gl_Position = reinterpret_cast<float *>(my_io->out_position);
        float *fragColor = reinterpret_cast<float *>(my_io->out_color);

        EXPECT_EQ(gl_Position[i * 7 + 0], fx);
        EXPECT_EQ(gl_Position[i * 7 + 1], fy);
        EXPECT_EQ(gl_Position[i * 7 + 2], fz);
        EXPECT_EQ(gl_Position[i * 7 + 3], fw);

        EXPECT_EQ(fragColor[i * 7 + 4], fr);
        EXPECT_EQ(fragColor[i * 7 + 5], fg);
        EXPECT_EQ(fragColor[i * 7 + 6], fb);        

        EXPECT_EQ(fx, fx);
        EXPECT_EQ(fy, fy);
        EXPECT_EQ(fz, fz);
        EXPECT_EQ(fw, fw);
    }
    
}
