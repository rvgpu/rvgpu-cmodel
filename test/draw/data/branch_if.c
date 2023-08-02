typedef struct {
    unsigned long input;
    unsigned long output;
} io;

long vs_main(long layout, long vid)
{
    int *input;
    int *output;

    // Global pointer 
    io *desc = (io *)layout;
    input = (int *)desc->input;
    output = (int *)desc->output;

    int a = input[vid];
    int out = a;
    if (vid % 2 == 0) {
        out = out + 100;
    }

    output[vid] = out;

    return 0;
}
