#include "../games101_config.hpp"
#include <eigen3/Eigen/Eigen>

struct triangle {
    Eigen::Vector4f v[3];
    Eigen::Vector3f color[3];
};

struct box_info {
    uint32_t box_l;
    uint32_t box_b;
    uint32_t box_width;
};

extern "C" {

void rasterization(
    long tid,
    struct triangle *in_triangle,
    uint8_t *out_color_buffer,
    float *out_depth_buffer,
    struct box_info *aux_box
) {
    uint32_t box_l = aux_box->box_l;
    uint32_t box_b = aux_box->box_b;
    uint32_t box_width = aux_box->box_width;
    
    uint32_t pixel_x = (tid % box_width) + box_l;
    uint32_t pixel_y = (tid / box_width) + box_b;

    struct triangle t = *in_triangle;

    float v0_x = t.v[0][0];
    float v0_y = t.v[0][1];
    float v1_x = t.v[1][0];
    float v1_y = t.v[1][1];    
    float v2_x = t.v[2][0];
    float v2_y = t.v[2][1];

    float center_x = pixel_x + 0.5f;
    float center_y = pixel_y + 0.5f;

    float denominator = (v0_x * v1_y - v0_y * v1_x) + (v1_x * v2_y - v1_y * v2_x) + (v2_x * v0_y - v2_y * v0_x);

    float bary0 = ((v1_y - v2_y) * center_x + (v2_x - v1_x) * center_y + (v1_x * v2_y - v1_y * v2_x)) / denominator;
    float bary1 = ((v2_y - v0_y) * center_x + (v0_x - v2_x) * center_y + (v2_x * v0_y - v2_y * v0_x)) / denominator;
    float bary2 = ((v0_y - v1_y) * center_x + (v1_x - v0_x) * center_y + (v0_x * v1_y - v0_y * v1_x)) / denominator;

    int pixel_in_triangle = (bary0 >= 0) && (bary1 >= 0) && (bary2 >= 0);

    // In-triangle test
    if (pixel_in_triangle) {        
        float v0_z = t.v[0][2];
        float v1_z = t.v[1][2];
        float v2_z = t.v[2][2];

        // Since z has gone through perspective projection, we use linear interpolation here
        float z = bary0 * v0_z + bary1 * v1_z + bary2 * v2_z;

        // Depth test
        // We use the convention 0 > n > f in projection, so nearer objects have larger z
        if (z > out_depth_buffer[(pixel_y * WIDTH) + pixel_x]) {
            out_depth_buffer[(pixel_y * WIDTH) + pixel_x] = z;
            
            Eigen::Vector3f color = bary0 * t.color[0] + bary1 * t.color[1] + bary2 * t.color[2];

            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 0] = (uint8_t)color[0];
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 1] = (uint8_t)color[1];
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 2] = (uint8_t)color[2];
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 3] = 255;
        }
    }

    return;
}

}
