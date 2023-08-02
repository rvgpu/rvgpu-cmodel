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
    for (int i=0; i<vid; i++) {
        out += i;
    }

    output[vid] = out;

    return 0;
}
