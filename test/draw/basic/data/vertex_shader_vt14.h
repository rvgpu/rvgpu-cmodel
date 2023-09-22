struct viewport {
    float x;
    float y;
    float w;
    float h;
};

// main block
float position[3][2] = {
        {-0.5, 0.5},
        {0.5, 0.5},
        {0, -0.5}
};

float colors[3][3] = {
        {0.0, 0.0, 1.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
};

void vertex_shader(long vid, float *out_position, float *out_color, struct viewport *vp)
{
    float fx = position[vid][0];
    float fy = position[vid][1];
    float fz = 0.0f;
    float fw = 1.0f;

    // viewport
    fx = vp->w + fx * (vp->w);
    fy = vp->h + fy * (vp->h);

    // output
    out_position[vid * 4 + 0] = fx;
    out_position[vid * 4 + 1] = fy;
    out_position[vid * 4 + 2] = fz;
    out_position[vid * 4 + 3] = fw;

    out_color[vid * 3 + 0] = colors[vid][0];
    out_color[vid * 3 + 1] = colors[vid][1];
    out_color[vid * 3 + 2] = colors[vid][2];

    return;
}
