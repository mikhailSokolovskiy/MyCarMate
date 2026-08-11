#pragma once

#include <cstdint>

#include "Happy_0.h"
#include "Happy_1.h"
#include "Happy_2.h"
#include "Happy_3.h"

constexpr const uint8_t *HappyFrames[] =
    {
        Happy_0,
        Happy_1,
        Happy_2,
        Happy_3,
    };

constexpr size_t HappyFrameCount = sizeof(HappyFrames) / sizeof(HappyFrames[0]);