long gpumain(long tid, int *input1, int *input2, int *output)
{
    int a = input1[tid];
    int b = input2[tid];
    int out = a * b;
    output[tid] = out;

    return 0;
}
