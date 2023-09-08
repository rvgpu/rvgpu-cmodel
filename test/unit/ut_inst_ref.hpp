#include <cstdint>

namespace ref {
    static inline uint64_t addi(uint64_t data, int32_t imm) {
        return (data + imm);
    }

    static inline uint64_t srai(uint64_t data, uint32_t imm) {
        return ((int64_t)data >> imm);
    }
};