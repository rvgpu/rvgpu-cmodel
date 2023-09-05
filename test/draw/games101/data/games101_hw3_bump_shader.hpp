#include "../games101_config.hpp"
#include <eigen3/Eigen/Eigen>

struct triangle {
    Eigen::Vector4f v[3];
    Eigen::Vector2f tex_coords[3];
    Eigen::Vector3f normal[3];
};

struct box_info {
    uint32_t box_l;
    uint32_t box_b;
    uint32_t box_width;
};

struct tex_info {
    uint8_t *tex_buffer;
    uint32_t tex_width;
    uint32_t tex_height;
};

extern "C" {

Eigen::Vector3f get_tex_color(uint8_t *tex_buffer, float tex_u, float tex_v, int w, int h) {
    int u_img = (int)(tex_u * w);
    int v_img = (int)((1 - tex_v) * h);

    uint8_t r = tex_buffer[(v_img * w + u_img) * 4 + 0];
    uint8_t g = tex_buffer[(v_img * w + u_img) * 4 + 1];
    uint8_t b = tex_buffer[(v_img * w + u_img) * 4 + 2];

    Eigen::Vector3f tex_color = {(float)r, (float)g, (float)b};

    return tex_color;
}

Eigen::Vector3f bump_shader_color(Eigen::Vector3f viewspace_normal, struct tex_info *tex, Eigen::Vector2f tex_coords) {
    float kh = 0.2, kn = 0.1;
    Eigen::Vector3f result_color = {0, 0, 0};

    // Normal
    Eigen::Vector3f normal = viewspace_normal;
    float x = normal.x();
    float y = normal.y();
    float z = normal.z();
    Eigen::Vector3f t(x * y / sqrt(x * x + z * z), sqrt(x * x + z * z), z * y / sqrt(x * x + z * z));
    Eigen::Vector3f b = normal.cross(t);

    Eigen::Matrix3f TBN;
    TBN << t.x(), b.x(), normal.x(), t.y(), b.y(), normal.y(), t.z(), b.z(), normal.z();

    // Texture
    int w = tex->tex_width;
    int h = tex->tex_height;
    uint8_t *tex_buffer = tex->tex_buffer;
    float tex_u = tex_coords[0];
    float tex_v = tex_coords[1];

    Eigen::Vector3f color0 = get_tex_color(tex_buffer, tex_u, tex_v, w, h);
    Eigen::Vector3f color1 = get_tex_color(tex_buffer, tex_u + (1 / (float)w), tex_v, w, h);
    Eigen::Vector3f color2 = get_tex_color(tex_buffer, tex_u, tex_v + (1 / (float)h), w, h);

    float dU = kh * kn * (color1.norm() - color0.norm());
    float dV = kh * kn * (color2.norm() - color0.norm());
    Eigen::Vector3f ln(-dU, -dV, 1.0);

    // Result color
    result_color = (TBN * ln).normalized();

    return result_color;
}

void bump_shader(
    long tid,
    struct triangle *in_triangle,
    uint8_t *out_color_buffer,
    float *out_depth_buffer,
    struct tex_info *tex,
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

            Eigen::Vector3f interpolated_normal = bary0 * t.normal[0] + bary1 * t.normal[1] + bary2 * t.normal[2];
            interpolated_normal = interpolated_normal.normalized();

            Eigen::Vector2f interpolated_texcoords = bary0 * t.tex_coords[0] + bary1 * t.tex_coords[1] + bary2 * t.tex_coords[2];

            Eigen::Vector3f color = bump_shader_color(interpolated_normal, tex, interpolated_texcoords);

            uint8_t color_r = (color[0] <= 0) ? 0 : (uint8_t)(color[0] * 255);
            uint8_t color_g = (color[1] <= 0) ? 0 : (uint8_t)(color[1] * 255);
            uint8_t color_b = (color[2] <= 0) ? 0 : (uint8_t)(color[2] * 255);
            
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 0] = color_r;
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 1] = color_g;
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 2] = color_b;
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 3] = 255;
        }
    }

    return;
}

}
