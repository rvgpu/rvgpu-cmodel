long gpumain(long tid, int *input, int *output)
{
    int a = input[tid];
    int out = a;
    for (int i=0; i<tid; i++) {
        out += i;
    }

    output[tid] = out;

    return 0;
}
