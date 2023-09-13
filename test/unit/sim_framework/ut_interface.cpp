#include <gtest/gtest.h>

#include "module/interface.hpp"

struct messages {
    uint32_t idata;
    float fdata;
};

class module_A {
public:
    module_A() {
        io_a = new interface<struct messages>();
    }

    interface<struct messages> *io_a;
};

class module_B {
public:
    module_B() {
        io_b = new interface<struct messages>();
    }

    interface<struct messages> *io_b;
};

TEST(simulator_framework_interface, connect_ok) {
    module_A *a = new module_A();
    module_B *b = new module_B();
    a->io_a->connect_to(b->io_b);

    a->io_a->write(messages {.idata = 0x1234, .fdata = 0.1234f});
    messages brdata = b->io_b->read();
    EXPECT_EQ(brdata.idata, 0x1234);
    EXPECT_FLOAT_EQ(brdata.fdata, 0.1234f);

    b->io_b->write(messages {.idata = 0x5678, .fdata = 0.5678f});
    messages ardata = a->io_a->read();
    EXPECT_EQ(ardata.idata, 0x5678);
    EXPECT_FLOAT_EQ(ardata.fdata, 0.5678f);
}
