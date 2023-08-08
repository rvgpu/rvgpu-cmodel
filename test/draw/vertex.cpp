#include "gpu_execuator.hpp"

#if 0
TEST_F(Draw, vertex_shader_vt14) {
    Shader shader;
    int32_t count = 3;    

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
    } io;

    struct viewport *my_vp = (struct viewport *) malloc(sizeof(struct viewport));
    my_vp->x = 0.0f;
    my_vp->y = 0.0f;
    my_vp->w = 400.0f;
    my_vp->h = 300.0f;

    float *my_position = (float *) malloc(count * 7 * sizeof(float));
    float *my_color = (float *) malloc(count * 7 * sizeof(float));

    io *my_io = (io *) malloc(sizeof(io));

    my_io->vp = reinterpret_cast<unsigned long>(my_vp);
    my_io->out_position = reinterpret_cast<unsigned long>(my_position);
    my_io->out_color = reinterpret_cast<unsigned long>(my_color);

    shader.SetupShaderBinary("vertex_shader_vt14.vs");

    vertex_command(count, (uint64_t)shader.binary, (uint64_t)my_io);

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

        fx = my_vp->w + fx * (my_vp->w);
        fy = my_vp->h + fy * (my_vp->h);

        float *gl_Position = reinterpret_cast<float *>(my_io->out_position);
        float *fragColor = reinterpret_cast<float *>(my_io->out_color);

        EXPECT_EQ(gl_Position[i * 7 + 0], fx);
        EXPECT_EQ(gl_Position[i * 7 + 1], fy);
        EXPECT_EQ(gl_Position[i * 7 + 2], fz);
        EXPECT_EQ(gl_Position[i * 7 + 3], fw);

        EXPECT_EQ(fragColor[i * 7 + 4], fr);
        EXPECT_EQ(fragColor[i * 7 + 5], fg);
        EXPECT_EQ(fragColor[i * 7 + 6], fb);
    }
}
#endif