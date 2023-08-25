#include "gpu_execuator.hpp"
#include "games101_common.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

struct viewport {
    float x;
    float y;
    float w;
    float h;
};

void gpumain(
    long tid,
    Eigen::Vector3f *in_positions,
    Eigen::Vector3f *out_positions,
    Eigen::Matrix4f *model,
    Eigen::Matrix4f *view,
    Eigen::Matrix4f *projection,
    struct viewport *vp
) {
    uint32_t vertex_id = tid;
    
    // MVP
    Eigen::Vector4f pos;
    pos << in_positions[vertex_id], 1.0;
    pos = (*projection) * (*view) * (*model) * pos;

    // Homogeneous division
    pos[0] /= pos[3];
    pos[1] /= pos[3];
    pos[2] /= pos[3];

    // Viewport transform
    float width = vp->w;
    float height = vp->h;
    float x = pos[0] * (width / 2) + (width / 2);
    float y = pos[1] * (height / 2) + (height / 2);
    float z = pos[2];

    Eigen::Vector3f xyz;
    xyz << x, y, z;

    out_positions[vertex_id] = xyz;

    return;
}

TEST_F(GPUExecuator, games101_hw1) {
    // 1. Data preparation
    // 1.1 Vertices
    Eigen::Vector3f vertex_positions[3] = {
        {2, 0, -2},
        {0, 2, -2},
        {-2, 0, -2}
    };
    
    // 1.2 Matrices
    float angle = 20;
    Eigen::Vector3f eye_pos = {0, 0, 5};

    Eigen::Matrix4f model = get_model_matrix(angle);
    Eigen::Matrix4f view = get_view_matrix(eye_pos);
    Eigen::Matrix4f projection = get_projection_matrix(45, 1, 0.1, 50);

    // 1.3 Viewport
    struct viewport *vp = (struct viewport *) malloc(sizeof(struct viewport));
    vp->x = 0.0f;
    vp->y = 0.0f;
    vp->w = WIDTH;
    vp->h = HEIGHT;



// --------------------



    // 2. Vertex shader
    Eigen::Vector3f vs_out_positions[3];
    Eigen::Vector3f vs_out_positions_reference[3];

    LoadELF("games101", "games101_hw1_vertex_shader");
    PushParam(0); // tid
    PushParam((uint64_t)vertex_positions);
    PushParam((uint64_t)vs_out_positions);
    PushParam((uint64_t)(&model));
    PushParam((uint64_t)(&view));
    PushParam((uint64_t)(&projection));
    PushParam((uint64_t)vp);
    run1d(3);

    for (int i = 0; i < 3; i++) {
        gpumain(i, vertex_positions, vs_out_positions_reference, &model, &view, &projection, vp);
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            EXPECT_FLOAT_EQ(vs_out_positions[i][j], vs_out_positions_reference[i][j]);
    }
}