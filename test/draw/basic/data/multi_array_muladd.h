long gpumain(long tid, int *input1, int *input2, int *input3, int *output)
{
    int a = input1[tid];
    int b = input2[tid];
    int c = input3[tid];
    int out = a * b + c;
    output[tid] = out;

    return 0;
}
