long gpumain(long tid, int *input, int *output)
{
    int a = input[tid];
    int out = a;
    if (tid % 2 == 0) {
        if (tid %4 == 0) {
            out = out + 400;
        } else {
            out = out + 200;
        }
    } else {
        out = out + 100;
    }

    output[tid] = out;

    return 0;
}
