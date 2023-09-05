#include "../games101_config.hpp"
#include <eigen3/Eigen/Eigen>

extern "C" {

void naive_bazier(
    long tid,
    Eigen::Vector2f *in_positions,
    uint8_t *out_color_buffer
) {
    Eigen::Vector2f p0 = in_positions[0];
    Eigen::Vector2f p1 = in_positions[1];
    Eigen::Vector2f p2 = in_positions[2];
    Eigen::Vector2f p3 = in_positions[3];

    float t = tid * 0.001;
    float s = 1 - t;

    Eigen::Vector2f point = s * s * s * p0 + 3 * t * s * s * p1 + 3 * t * t * s * p2 + t * t * t * p3;

    uint32_t x = (uint32_t)(point.x());
    uint32_t y = (uint32_t)(point.y());

    out_color_buffer[((y * WIDTH) + x) * 4 + 0] = 255;
    out_color_buffer[((y * WIDTH) + x) * 4 + 1] = 255;
    out_color_buffer[((y * WIDTH) + x) * 4 + 3] = 255;

    return;
}

}
