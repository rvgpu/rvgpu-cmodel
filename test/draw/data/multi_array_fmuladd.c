typedef struct {
    unsigned long input1;
    unsigned long input2;
    unsigned long input3;
    unsigned long output;
} io;

long vs_main(long layout, long vid)
{
    float *input1;
    float *input2;
    float *input3;
    float *output;

    // Global pointer 
    io *desc = (io *)layout;
    input1 = (float *)desc->input1;
    input2 = (float *)desc->input2;
    input3 = (float *)desc->input3;
    output = (float *)desc->output;

    float a = input1[vid];
    float b = input2[vid];
    float c = input3[vid];
    float out = a * b + c;
    output[vid] = out;

    return 0;
}
