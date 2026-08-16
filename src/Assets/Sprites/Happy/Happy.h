#pragma once

#include <cstdint>

#include "Happy_0.h"
#include "Happy_1.h"
#include "Happy_2.h"
#include "Happy_3.h"
#include "Happy_4.h"
#include "Happy_5.h"
#include "Happy_6.h"
#include "Happy_7.h"

constexpr const uint8_t *HappyFrames[] =
    {
        Happy_0,
        Happy_1,
        Happy_2,
        Happy_3,
        Happy_4,
        Happy_5,
        Happy_6,
        Happy_7,
    };

constexpr size_t HappyFrameCount = sizeof(HappyFrames) / sizeof(HappyFrames[0]);