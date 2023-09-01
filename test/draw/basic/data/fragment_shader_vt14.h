#define WIDTH 800

long gpumain(long pixel, float *in_position, float *in_color, unsigned char *out_color_buffer, int v0_id, int v1_id, int v2_id)
{
    unsigned int pixel_x = pixel % 800;
    unsigned int pixel_y = pixel / 800;

    float v0_x = in_position[v0_id * 4 + 0];
    float v0_y = in_position[v0_id * 4 + 1];
    float v1_x = in_position[v1_id * 4 + 0];
    float v1_y = in_position[v1_id * 4 + 1];
    float v2_x = in_position[v2_id * 4 + 0];
    float v2_y = in_position[v2_id * 4 + 1];

    float v0_r = in_color[v0_id * 3 + 0];
    float v0_g = in_color[v0_id * 3 + 1];
    float v0_b = in_color[v0_id * 3 + 2];
    float v1_r = in_color[v1_id * 3 + 0];
    float v1_g = in_color[v1_id * 3 + 1];
    float v1_b = in_color[v1_id * 3 + 2];
    float v2_r = in_color[v2_id * 3 + 0];
    float v2_g = in_color[v2_id * 3 + 1];
    float v2_b = in_color[v2_id * 3 + 2];

    float center_x = pixel_x + 0.5f;
    float center_y = pixel_y + 0.5f;

    float denominator = (v0_x * v1_y - v0_y * v1_x) + (v1_x * v2_y - v1_y * v2_x) + (v2_x * v0_y - v2_y * v0_x);

    float bary0 = ((v1_y - v2_y) * center_x + (v2_x - v1_x) * center_y + (v1_x * v2_y - v1_y * v2_x)) / denominator;
    float bary1 = ((v2_y - v0_y) * center_x + (v0_x - v2_x) * center_y + (v2_x * v0_y - v2_y * v0_x)) / denominator;
    float bary2 = ((v0_y - v1_y) * center_x + (v1_x - v0_x) * center_y + (v0_x * v1_y - v0_y * v1_x)) / denominator;

    int pixel_in_triangle = (bary0 >= 0) && (bary1 >= 0) && (bary2 >= 0);

    if (pixel_in_triangle) {
        float color_r = bary0 * v0_r + bary1 * v1_r + bary2 * v2_r;
        float color_g = bary0 * v0_g + bary1 * v1_g + bary2 * v2_g;
        float color_b = bary0 * v0_b + bary1 * v1_b + bary2 * v2_b;

        out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 0] = (unsigned char)(color_r * 255);
        out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 1] = (unsigned char)(color_g * 255);
        out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 2] = (unsigned char)(color_b * 255);
        out_color_buffer[(pixel_y * WIDTH + pixel_x) * 4 + 3] = 255;
    } else {
        // Do nothing
    }

    return 0;
}
