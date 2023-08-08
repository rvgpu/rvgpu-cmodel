long gpumain(long tid, int *input, int* output)
{
    int a = input[tid];
    int out = a + 100;
    output[tid] = out;

    return 0;
}
