long gpumain(long tid, float *input1, float *input2, float *input3, float *output)
{
    float a = input1[tid];
    float b = input2[tid];
    float c = input3[tid];
    float out = a * b + c;
    output[tid] = out;

    return 0;
}
