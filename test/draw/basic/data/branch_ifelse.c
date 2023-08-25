long gpumain(long tid, int *input, int *output)
{
    int a = input[tid];
    int out = a;
    if (tid % 2 == 0) {
        out = out + 100;
    } else {
        out = out + 200;
    }

    output[tid] = out;
    return 0;
}
