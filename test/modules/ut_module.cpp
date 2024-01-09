#include <gtest/gtest.h>

#include "modules/modules.hpp"
#include "modules/interface.hpp"

struct messages {
    uint32_t idata;
    float fdata;
    float res;
};

class module_A : public modules {
public:
    module_A(std::string name) : modules(name) {
        io_m = new interface<messages>(this);
    }

    void runner() override {
        messages rdata = io_m->read();
        printf("a: rdata.idata: %d\n", rdata.idata);
        printf("a: rdata.fdata: %f\n", rdata.fdata);
        printf("a: rdata.fdata: %f\n", rdata.res);
        fflush(stdout);

        res = rdata.res;
    }

    interface<messages> *io_m;

    float res;
};

class module_B : public modules {
public:
    module_B(std::string name) : modules(name) {
        io_s = new interface<messages>(this);
    }

    void runner() override {
        messages rdata = io_s->read();
        rdata.res = rdata.idata * rdata.fdata;
        idata = rdata.idata;
        fdata = rdata.fdata;

        printf("b: rdata.idata: %d\n", rdata.idata);
        printf("b: rdata.fdata: %f\n", rdata.fdata);
        fflush(stdout);

        io_s->write(rdata);
    }

    interface<messages> *io_s;
    uint32_t idata;
    float fdata;
};

TEST(simulator_framework_module, new_module_ok) {
    module_A *a = new module_A("module A");
    module_B *b = new module_B("module B");
    a->io_m->connect_to(b->io_s);

    a->io_m->write(messages{.idata = 0x1234, .fdata = 0.1234f, .res = 0});

    sleep(1);
    EXPECT_EQ(b->idata, 0x1234);
    EXPECT_FLOAT_EQ(b->fdata, 0.1234);
    EXPECT_FLOAT_EQ(a->res, (0x1234 * 0.1234));
    delete a;
}
