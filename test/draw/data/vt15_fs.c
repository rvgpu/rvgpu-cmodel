
typedef struct {
    unsigned long in_position;
    unsigned long in_color;
    unsigned long out_color;
} io;

long vs_main(long layout, long xy, long v0v1, long v2)
{
    /* Global Pointer */
    io *desc = (io *)layout;

    unsigned int x = xy & 0xffffffff;
    unsigned int y = xy >> 32;
    unsigned int v0 = v0v1 & 0xffffffff;
    unsigned int v1 = v0v1 >> 32;

    return 0;
}
