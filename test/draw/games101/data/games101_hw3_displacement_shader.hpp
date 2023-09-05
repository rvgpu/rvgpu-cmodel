#include "../games101_config.hpp"
#include <eigen3/Eigen/Eigen>

struct triangle {
    Eigen::Vector4f v[3];
    Eigen::Vector3f color[3];
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

struct light {
    Eigen::Vector3f position;
    Eigen::Vector3f intensity;
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

void bump_shader_modify(Eigen::Vector3f *point, Eigen::Vector3f *normal, struct tex_info *tex, Eigen::Vector2f tex_coords) {
    float kh = 0.2, kn = 0.1;

    // Normal
    float x = normal->x();
    float y = normal->y();
    float z = normal->z();
    Eigen::Vector3f t(x * y / sqrt(x * x + z * z), sqrt(x * x + z * z), z * y / sqrt(x * x + z * z));
    Eigen::Vector3f b = normal->cross(t);

    Eigen::Matrix3f TBN;
    TBN << t.x(), b.x(), normal->x(), t.y(), b.y(), normal->y(), t.z(), b.z(), normal->z();

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

    // Modified point
    *point = *point + kn * (*normal) * color0.norm();

    // Modified normal
    *normal = (TBN * ln).normalized();
}

Eigen::Vector3f phong_shader_color(Eigen::Vector3f color, Eigen::Vector3f viewspace_normal, Eigen::Vector3f viewspace_pos) {
    Eigen::Vector3f ka = Eigen::Vector3f(0.005, 0.005, 0.005);
    Eigen::Vector3f kd = color;
    Eigen::Vector3f ks = Eigen::Vector3f(0.7937, 0.7937, 0.7937);

    Eigen::Vector3f eye_pos{0, 0, 10};
    float p = 150;

    Eigen::Vector3f result_color = {0, 0, 0};

    // Lights
    Eigen::Vector3f point = viewspace_pos;
    Eigen::Vector3f normal = viewspace_normal;

    auto l1 = light{{20, 20, 20}, {500, 500, 500}};
    auto l2 = light{{-20, 20, 0}, {500, 500, 500}};
    std::vector<light> lights = {l1, l2};
    Eigen::Vector3f amb_light_intensity{10, 10, 10};

    for (auto& light : lights) {
        Eigen::Vector3f La;
        Eigen::Vector3f Ld;
        Eigen::Vector3f Ls;

        Eigen::Vector3f l = (light.position - point).normalized();
        Eigen::Vector3f v = (eye_pos - point).normalized();
        Eigen::Vector3f h = (v + l).normalized();

        // Ambient lights
        for (int i = 0; i < 3; i++) {
            La[i] = ka[i] * amb_light_intensity[i];
        }

        // Diffuse lights
        if (normal.dot(l) > 0.0) {
            for (int i = 0; i < 3; i++) {
                Ld[i] = kd[i] * light.intensity[i] / (light.position - point).dot(light.position - point) * normal.dot(l);
            }
        } else {
            Ld << 0.0, 0.0, 0.0;
        }

        // Specular lights
        if (normal.dot(h) > 0.0) {
            for (int i = 0; i < 3; i++) {
                Ls[i] = ks[i] * light.intensity[i] / (light.position - point).dot(light.position - point) * std::pow(normal.dot(h), p);
            }
        } else {
            Ls << 0.0, 0.0, 0.0;
        }

        result_color += La + Ld + Ls;
    }

    return result_color;
}

Eigen::Vector3f displacement_shader_color(Eigen::Vector3f color, Eigen::Vector3f viewspace_normal, struct tex_info *tex, Eigen::Vector2f tex_coords, Eigen::Vector3f viewspace_pos) {
    Eigen::Vector3f result_color = {0, 0, 0};

    Eigen::Vector3f point = viewspace_pos;
    Eigen::Vector3f normal = viewspace_normal;
    
    // Use bump shader to modify the point and the normal
    bump_shader_modify(&point, &normal, tex, tex_coords);

    // Use phong shader to compute the color
    result_color = phong_shader_color(color, normal, point);    

    return result_color;
}

void displacement_shader(
    long tid,
    struct triangle *in_triangle,
    uint8_t *out_color_buffer,
    float *out_depth_buffer,
    struct tex_info *tex,
    struct box_info *aux_box,
    Eigen::Vector4f *aux_viewspace_pos
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

            Eigen::Vector3f interpolated_color = bary0 * t.color[0] + bary1 * t.color[1] + bary2 * t.color[2];

            Eigen::Vector2f interpolated_texcoords = bary0 * t.tex_coords[0] + bary1 * t.tex_coords[1] + bary2 * t.tex_coords[2];

            Eigen::Vector3f interpolated_normal = bary0 * t.normal[0] + bary1 * t.normal[1] + bary2 * t.normal[2];
            interpolated_normal = interpolated_normal.normalized();            

            Eigen::Vector3f interpolated_pos = bary0 * aux_viewspace_pos[0].head<3>() + bary1 * aux_viewspace_pos[1].head<3>() + bary2 * aux_viewspace_pos[2].head<3>();

            Eigen::Vector3f color = displacement_shader_color(interpolated_color, interpolated_normal, tex, interpolated_texcoords, interpolated_pos);
            
            uint8_t color_r =
                (color[0] <= 0) ? 0 :
                (color[0] >= 1) ? 255 :
                (uint8_t)(color[0] * 255);
            uint8_t color_g =
                (color[1] <= 0) ? 0 :
                (color[1] >= 1) ? 255 :
                (uint8_t)(color[1] * 255);
            uint8_t color_b =
                (color[2] <= 0) ? 0 :
                (color[2] >= 1) ? 255 :
                (uint8_t)(color[2] * 255);
            
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 0] = color_r;
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 1] = color_g;
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 2] = color_b;
            out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 3] = 255;
        }
    }

    return;
}

}
