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

void gpumain(
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

    float bary0 = (v1_x - center_x) * (v2_y - center_y) - (v2_x - center_x) * (v1_y - center_y);    
    float bary1 = (v2_x - center_x) * (v0_y - center_y) - (v0_x - center_x) * (v2_y - center_y);
    float bary2 = (v0_x - center_x) * (v1_y - center_y) - (v1_x - center_x) * (v0_y - center_y);

    int pixel_in_triangle = ((bary0 >= 0) && (bary1 >= 0) && (bary2 >= 0)) || ((bary0 <= 0) && (bary1 <= 0) && (bary2 <= 0));

    // In-triangle test
    if (pixel_in_triangle) {        
        float v0_z = t.v[0][2];
        float v1_z = t.v[1][2];
        float v2_z = t.v[2][2];

        bary0 /= ((v1_x - v0_x) * (v2_y - v0_y) - (v2_x - v0_x) * (v1_y - v0_y));
        bary1 /= ((v2_x - v1_x) * (v0_y - v1_y) - (v0_x - v1_x) * (v2_y - v1_y));
        bary2 /= ((v0_x - v2_x) * (v1_y - v2_y) - (v1_x - v2_x) * (v0_y - v2_y));

        // Since z has gone through perspective projection, we use linear interpolation here
        float z = bary0 * v0_z + bary1 * v1_z + bary2 * v2_z;

        // Depth test
        // We use the convention 0 > n > f in projection, so nearer objects have larger z
        if (z > out_depth_buffer[(pixel_y * WIDTH) + pixel_x]) {
            out_depth_buffer[(pixel_y * WIDTH) + pixel_x] = z;

            float v0_r = t.color[0][0];
            float v0_g = t.color[0][1];
            float v0_b = t.color[0][2];
            float v1_r = t.color[1][0];
            float v1_g = t.color[1][1];
            float v1_b = t.color[1][2];
            float v2_r = t.color[2][0];
            float v2_g = t.color[2][1];
            float v2_b = t.color[2][2];

            // Since attributes (such as color) have not gone through perspective projection, we use perspective-corrected interpolation here
            float v0_w = t.v[0][3];
            float v1_w = t.v[1][3];
            float v2_w = t.v[2][3];            
            float a = bary0 / v0_w;
            float b = bary1 / v1_w;
            float c = bary2 / v2_w;
            bary0 = a / (a + b + c);
            bary1 = b / (a + b + c);
            bary2 = c / (a + b + c);

            float color_r = bary0 * v0_r + bary1 * v1_r + bary2 * v2_r;
            float color_g = bary0 * v0_g + bary1 * v1_g + bary2 * v2_g;
            float color_b = bary0 * v0_b + bary1 * v1_b + bary2 * v2_b;
            
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 0] = (uint8_t)color_r;
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 1] = (uint8_t)color_g;
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 2] = (uint8_t)color_b;
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 3] = 255;
        }
    }

    return;
}

}
