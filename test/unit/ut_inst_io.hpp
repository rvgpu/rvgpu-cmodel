#pragma once
#include <cstdint>

#include "common/regid.hpp"
#include "common/utils.hpp"

class IN {
public:
    IN(reg regid, uint64_t data) : first(regid), second(uint64_t(data)) {}
    IN(reg regid, int64_t data)  : first(regid), second(uint64_t(data)) {}
    IN(reg regid, uint32_t data) : first(regid), second(uint64_t(data)) {}
    IN(reg regid, int32_t  data) : first(regid), second(uint64_t(data)) {}
    IN(reg regid, double ddata)  : first(regid), second(utils::d2ul(ddata)) {}
    IN(reg regid, float ddata)   : first(regid), second(utils::f2ul(ddata)) {}

    reg first;
    uint64_t second;
};

class RES {
public:
    RES(reg regid, uint64_t data) : first(regid), second(uint64_t(data)) {}
    RES(reg regid, int64_t data)  : first(regid), second(uint64_t(data)) {}
    RES(reg regid, uint32_t data) : first(regid), second(uint64_t(data)) {}
    RES(reg regid, int32_t  data) : first(regid), second(uint64_t(data)) {}
    RES(reg regid, double ddata)  : first(regid), second(utils::d2ul(ddata)) {}
    RES(reg regid, float ddata)   : first(regid), second(utils::f2ul(ddata)) {}

    reg first;
    uint64_t second;
};