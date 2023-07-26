#include "../../../src/cs/cmd_stream.h"

int *input;
int *output;

//                a0            a1
long vs_main(long descptr, long vid)
{
    // Global pointer 
    cmd_stream_vs *desc = (cmd_stream_vs *)descptr;
    input = (int *)desc->input;
    output = (int *)desc->output;

    int a = input[vid];
    int out = a + 100;
    output[vid] = out;

    return 0;
}
