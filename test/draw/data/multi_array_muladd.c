typedef struct {
    unsigned long input1;
    unsigned long input2;
    unsigned long input3;
    unsigned long output;
} io;

long vs_main(long layout, long vid)
{
    int *input1;
    int *input2;
    int *input3;
    int *output;

    // Global pointer 
    io *desc = (io *)layout;
    input1 = (int *)desc->input1;
    input2 = (int *)desc->input2;
    input3 = (int *)desc->input3;
    output = (int *)desc->output;

    int a = input1[vid];
    int b = input2[vid];
    int c = input3[vid];
    int out = a * b + c;
    output[vid] = out;

    return 0;
}
