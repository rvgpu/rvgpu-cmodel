#include "../games101_config.hpp"
#include <eigen3/Eigen/Eigen>

extern "C" {

void vertex_shader(
    long tid,
    Eigen::Vector3f *in_positions,
    Eigen::Vector4f *out_positions,
    Eigen::Matrix4f *aux_model,
    Eigen::Matrix4f *aux_view,
    Eigen::Matrix4f *aux_projection
) {
    uint32_t vertex_id = tid;
    
    // MVP
    Eigen::Vector4f pos;
    pos << in_positions[vertex_id], 1.0;
    pos = (*aux_projection) * (*aux_view) * (*aux_model) * pos;

    // Homogeneous division
    pos[0] /= pos[3];
    pos[1] /= pos[3];
    pos[2] /= pos[3];

    // Viewport transform
    // (x, y) is in the screen space
    float x = pos[0] * (WIDTH / 2) + (WIDTH / 2);
    float y = pos[1] * (HEIGHT / 2) + (HEIGHT / 2);

    // z is between -1.0 (far) and 1.0 (near)
    float z = pos[2];

    // w is the original z before perspective projection
    float w = pos[3];

    Eigen::Vector4f xyzw;
    xyzw << x, y, z, w;

    out_positions[vertex_id] = xyzw;

    return;
}

}
