#include <eigen3/Eigen/Eigen>

struct viewport {
    float x;
    float y;
    float w;
    float h;
};

extern "C" {

void gpumain(
    long tid,
    Eigen::Vector3f *in_positions,
    Eigen::Vector4f *out_positions,
    Eigen::Matrix4f *aux_model,
    Eigen::Matrix4f *aux_view,
    Eigen::Matrix4f *aux_projection,
    struct viewport *aux_vp
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
    float width = aux_vp->w;
    float height = aux_vp->h;
    float x = pos[0] * (width / 2) + (width / 2);
    float y = pos[1] * (height / 2) + (height / 2);
    float z = pos[2];
    float w = pos[3];

    Eigen::Vector4f xyzw;
    xyzw << x, y, z, w;

    out_positions[vertex_id] = xyzw;

    return;
}

}
