#include "gpu_execuator.hpp"

TEST_F(GPUExecuator, branch_if) {
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    LoadELF("branch_if");
    PushParam(0);
    PushParam((uint64_t)in);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        if (i%2 == 0) {
            EXPECT_EQ(out[i], in[i] + 100);
        } else {
            EXPECT_EQ(out[i], in[i]);
        }
    }
}

TEST_F(GPUExecuator, branch_ifelse) {
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    LoadELF("branch_ifelse");
    PushParam(0);
    PushParam((uint64_t)in);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        if (i%2 == 0) {
            EXPECT_EQ(out[i], in[i] + 100);
        } else {
            EXPECT_EQ(out[i], in[i] + 200);
        }
    }
}

TEST_F(GPUExecuator, branch_ifif) {
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    LoadELF("branch_ifif");
    PushParam(0);
    PushParam((uint64_t)in);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        if (i%2 == 0) {
            if (i%4 == 0) {
                EXPECT_EQ(out[i], in[i] + 400);
            } else {
                EXPECT_EQ(out[i], in[i] + 200);
            }
        } else {
            EXPECT_EQ(out[i], in[i] + 100);
        }
    }
}

TEST_F(GPUExecuator, branch_for) {
    int32_t count = 32;
    int i = 0;
    uint32_t *in = (uint32_t *)malloc(count * sizeof(int));
    uint32_t *out = (uint32_t *)malloc(count * sizeof(int));

    LoadELF("branch_for");
    PushParam(0);
    PushParam((uint64_t)in);
    PushParam((uint64_t)out);

    for (i=0; i<count; i++) {
        in[i] = i * 100;
        out[i] = 5678;   // test of array[i] + 100;
    }

    run1d(count);

    for (i=0; i<count; i++) {
        uint32_t expect_out = in[i];
        for (int j=0; j<i; j++) {
            expect_out += j;
        }

        EXPECT_EQ(out[i], expect_out);
    }
}