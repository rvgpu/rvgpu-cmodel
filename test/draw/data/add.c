typedef struct {
    unsigned long input;
    unsigned long output;
} this_layout;

long vs_main(long descptr, long vid)
{
    int *input;
    int *output;

    // Global pointer 
    this_layout *desc = (this_layout *)descptr;
    input = (int *)desc->input;
    output = (int *)desc->output;

    int a = input[vid];
    int out = a + 100;
    output[vid] = out;

    return 0;
}
