struct viewport {
    float x;
    float y;
    float w;
    float h;
};

typedef struct {
    unsigned long vp;
    unsigned long out_position;
    unsigned long out_color;
} io;

long vs_main(long layout, long vid)
{
    /* Global Pointer */
    io *desc = (io *)layout;
    float *gl_Position = (float *)desc->out_position;
    float *fragColor = (float *)desc->out_color;

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

    float fx = position[vid][0];
    float fy = position[vid][1];
    float fz = 0.0f;
    float fw = 1.0f;
    float fr = colors[vid][0];
    float fg = colors[vid][1];
    float fb = colors[vid][2];

    // viewport
    struct viewport *vp;
    vp = (struct viewport *)(desc->vp);

    fx = vp->x + fx * (vp->w) / 2;
    fy = vp->y + fy * (vp->h) / 2;

    // output
    gl_Position[vid * 7 + 0] = fx;
    gl_Position[vid * 7 + 1] = fy;
    gl_Position[vid * 7 + 2] = fz;
    gl_Position[vid * 7 + 3] = fw;

    fragColor[vid * 7 + 4] = fr;
    fragColor[vid * 7 + 5] = fg;
    fragColor[vid * 7 + 6] = fb;

    return 0;
}
