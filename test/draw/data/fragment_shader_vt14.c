#define WIDTH 800

typedef struct {
    unsigned long in_position;
    unsigned long in_color;
    unsigned long out_color_buffer;
} io;

long gpumain(uint32_t x, uint32_t y, float *in_position, uint32_t v0, uint32_t v1, uint32_t v2)
{
    /* Global Pointer */
    io *desc = (io *)layout;

    float *in_position = (float *)desc->in_position;
    float *in_color = (float *)desc->in_color;
    unsigned char *out_color_buffer = (unsigned char *)desc->out_color_buffer;

    unsigned int pixel_x = (unsigned int)(pixel & ((1L << 32) - 1));
    unsigned int pixel_y = (unsigned int)(pixel >> 32);
    unsigned int v0_id = (unsigned int)(v01 & ((1L << 32) - 1));
    unsigned int v1_id = (unsigned int)(v01 >> 32);
    unsigned int v2_id = (unsigned int)(v2 & ((1L << 32) - 1));

    float v0_x = in_position[v0_id * 7 + 0];
    float v0_y = in_position[v0_id * 7 + 1];
    float v1_x = in_position[v1_id * 7 + 0];
    float v1_y = in_position[v1_id * 7 + 1];
    float v2_x = in_position[v2_id * 7 + 0];
    float v2_y = in_position[v2_id * 7 + 1];

    float v0_r = in_color[v0_id * 7 + 4];
    float v0_g = in_color[v0_id * 7 + 5];
    float v0_b = in_color[v0_id * 7 + 6];
    float v1_r = in_color[v1_id * 7 + 4];
    float v1_g = in_color[v1_id * 7 + 5];
    float v1_b = in_color[v1_id * 7 + 6];
    float v2_r = in_color[v2_id * 7 + 4];
    float v2_g = in_color[v2_id * 7 + 5];
    float v2_b = in_color[v2_id * 7 + 6];

    float denominator = (v0_x * v1_y - v0_y * v1_x) + (v1_x * v2_y - v1_y * v2_x) + (v2_x * v0_y - v2_y * v0_x);

    float coeff0_x = (v1_y - v2_y) / denominator;
    float coeff0_y = (v2_x - v1_x) / denominator;
    float coeff0_const = (v1_x * v2_y - v1_y * v2_x) / denominator;

    float coeff1_x = (v2_y - v0_y) / denominator;
    float coeff1_y = (v0_x - v2_x) / denominator;
    float coeff1_const = (v2_x * v0_y - v2_y * v0_x) / denominator;

    float coeff2_x = (v0_y - v1_y) / denominator;
    float coeff2_y = (v1_x - v0_x) / denominator;
    float coeff2_const = (v0_x * v1_y - v0_y * v1_x) / denominator;

    float pixel_center_x = pixel_x + 0.5f;
    float pixel_center_y = pixel_y + 0.5f;

    float barycentric0 = coeff0_x * pixel_center_x + coeff0_y * pixel_center_y + coeff0_const;
    float barycentric1 = coeff1_x * pixel_center_x + coeff1_y * pixel_center_y + coeff1_const;
    float barycentric2 = coeff2_x * pixel_center_x + coeff2_y * pixel_center_y + coeff2_const;

    int pixel_in_triangle = ((barycentric0 >= 0) && (barycentric1 >= 0) && (barycentric2 >= 0)) || ((barycentric0 <= 0) && (barycentric1 <= 0) && (barycentric2 <= 0));

    if (pixel_in_triangle) {
        float interpolate_r = barycentric0 * v0_r + barycentric1 * v1_r + barycentric2 * v2_r;
        float interpolate_g = barycentric0 * v0_g + barycentric1 * v1_g + barycentric2 * v2_g;
        float interpolate_b = barycentric0 * v0_b + barycentric1 * v1_b + barycentric2 * v2_b;

        out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 0] = (unsigned char)(interpolate_r * 255);
        out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 1] = (unsigned char)(interpolate_g * 255);
        out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 2] = (unsigned char)(interpolate_b * 255);
        out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 3] = 255;
    } else {
        // Do nothing
    }

    return 0;
}
