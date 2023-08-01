#pragma once

#define FOREACH_WARP_THREAD \
    for (uint32_t thread=0; thread<WARP_THREAD_N; thread++)
