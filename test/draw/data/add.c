#include "../../../src/cp/command_stream.h"

//                a0            a1
long vs_main(long descptr, long vid)
{
    int *input;
    int *output;

    // Global pointer 
    cs_vs_desc *desc = (cs_vs_desc *)descptr;
    input = (int *)desc->input;
    output = (int *)desc->output;

    int a = input[vid];
    int out = a + 100;
    output[vid] = out;

    return 0;
}
