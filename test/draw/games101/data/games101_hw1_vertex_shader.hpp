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

}
