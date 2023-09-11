#include <cmath>

constexpr double MY_PI = 3.1415926;

#define TEST_LINE   (idx ++);

extern "C" {

void testmath(long tid, float *in1, float *in2, float *out) {
    int idx = -1;
    TEST_LINE out[idx] = std::cos(in1[idx] / 180.0f * MY_PI);       // cos(x)
    TEST_LINE out[idx] = std::sin(in1[idx] / 180.0f * MY_PI);       // sin(x)
    TEST_LINE out[idx] = std::pow(in1[idx], in2[idx]);              // pow(x, y)
}
}
