#include <cstdint>

namespace ref {
    static inline uint64_t addi(uint64_t src1, int32_t imm) {
        return (src1 + imm);
    }

    static inline uint64_t srai(uint64_t src1, uint32_t imm) {
        return ((int64_t)src1 >> imm);
    }

    static inline uint64_t div_i64(uint64_t src1, uint64_t src2) {
        return (uint64_t)(int64_t(src1) / int64_t(src2));
    }

    static inline uint64_t div_u64(uint64_t src1, uint64_t src2) {
        return (uint64_t)(src1 / src2);
    }
};