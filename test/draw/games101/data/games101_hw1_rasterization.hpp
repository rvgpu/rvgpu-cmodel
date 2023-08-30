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
    float *in_line_endpoints,
    float *in_line_attributes,
    uint8_t *out_color_buffer,
    uint32_t *aux_start,
    uint8_t *aux_is_x_major,    
    uint32_t *aux_width
) {
    uint32_t axis = tid + (*aux_start);

    float p0 = in_line_endpoints[0];
    float p1 = in_line_endpoints[1];
    float a0 = in_line_attributes[0];
    float a1 = in_line_attributes[1];
    
    // Line interpolation of attributes
    float t = (axis - p0) / (p1 - p0);
    uint32_t result = (uint32_t)((1.0 - t) * a0 + t * a1);

    if (*aux_is_x_major) {
        // axis is x, result is y
        uint32_t pixel_id = result * (*aux_width) + axis;
        out_color_buffer[pixel_id * 4 + 0] = 255;
        out_color_buffer[pixel_id * 4 + 1] = 255;
        out_color_buffer[pixel_id * 4 + 2] = 255;
        out_color_buffer[pixel_id * 4 + 3] = 255;
    } else {
        // axis is y, result is x
        uint32_t pixel_id = axis * (*aux_width) + result;
        out_color_buffer[pixel_id * 4 + 0] = 255;
        out_color_buffer[pixel_id * 4 + 1] = 255;
        out_color_buffer[pixel_id * 4 + 2] = 255;
        out_color_buffer[pixel_id * 4 + 3] = 255;
    }

    return;
}

}
