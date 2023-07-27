typedef struct {
    unsigned long input1;
    unsigned long input2;
    unsigned long output;
} io;

long vs_main(long layout, long vid)
{
    int *input1;
    int *input2;
    int *output;

    // Global pointer 
    io *desc = (io *)layout;
    input1 = (int *)desc->input1;
    input2 = (int *)desc->input2;
    output = (int *)desc->output;

    int a = input1[vid];
    int b = input2[vid];
    int out = a + b;
    output[vid] = out;

    return 0;
}
