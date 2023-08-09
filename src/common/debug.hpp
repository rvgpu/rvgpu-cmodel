#pragma once

#include "common/configs.h"

#if RVGPU_DEBUG
#define RVGPU_DEBUG_PRINT(msg, ...)     printf(msg, ##__VA_ARGS__)
#else
#define RVGPU_DEBUG_PRINT(msg, ...)
#endif

#define RVGPU_ERROR_PRINT(msg, ...)     printf(msg, ##__VA_ARGS__)
#define ALU_INFO(msg, ...)              RVGPU_DEBUG_PRINT("[ALU.%d]" msg, m_id, ##__VA_ARGS__)
#define FPU_INFO(msg, ...)              RVGPU_DEBUG_PRINT("[FPU.%d]" msg, m_id, ##__VA_ARGS__)

