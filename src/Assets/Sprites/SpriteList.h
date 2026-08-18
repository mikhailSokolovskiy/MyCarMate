#pragma once

#include <cstddef>
#include <cstdint>

#include "Happy/Happy_0.h"
#include "Happy/Happy_1.h"
#include "Happy/Happy_2.h"
#include "Happy/Happy_3.h"
#include "Happy/Happy_4.h"
#include "Happy/Happy_5.h"
#include "Happy/Happy_6.h"
#include "Happy/Happy_7.h"

// === Angry ===
#include "Angry/Angry_0.h"
#include "Angry/Angry_1.h"
#include "Angry/Angry_2.h"
#include "Angry/Angry_3.h"
#include "Angry/Angry_4.h"
#include "Angry/Angry_5.h"
#include "Angry/Angry_6.h"
#include "Angry/Angry_7.h"

#include "Dizzy/Dizzy_0.h"
#include "Dizzy/Dizzy_1.h"
#include "Dizzy/Dizzy_2.h"
#include "Dizzy/Dizzy_3.h"
#include "Dizzy/Dizzy_4.h"
#include "Dizzy/Dizzy_5.h"
#include "Dizzy/Dizzy_6.h"
#include "Dizzy/Dizzy_7.h"

#include "Blink/Blink_0.h"
#include "Blink/Blink_1.h"
#include "Blink/Blink_2.h"
#include "Blink/Blink_3.h"
#include "Blink/Blink_4.h"
#include "Blink/Blink_5.h"
#include "Blink/Blink_6.h"
#include "Blink/Blink_7.h"

#include "Sleep/Sleep_0.h"
#include "Sleep/Sleep_1.h"
#include "Sleep/Sleep_2.h"
#include "Sleep/Sleep_3.h"
#include "Sleep/Sleep_4.h"
#include "Sleep/Sleep_5.h"
#include "Sleep/Sleep_6.h"
#include "Sleep/Sleep_7.h"

#include "Surprise/Surprise_0.h"
#include "Surprise/Surprise_1.h"
#include "Surprise/Surprise_2.h"
#include "Surprise/Surprise_3.h"
#include "Surprise/Surprise_4.h"
#include "Surprise/Surprise_5.h"
#include "Surprise/Surprise_6.h"
#include "Surprise/Surprise_7.h"

#include "ShiftLeft/ShiftLeft_0.h"
#include "ShiftLeft/ShiftLeft_1.h"
#include "ShiftLeft/ShiftLeft_2.h"
#include "ShiftLeft/ShiftLeft_3.h"
#include "ShiftLeft/ShiftLeft_4.h"
#include "ShiftLeft/ShiftLeft_5.h"
#include "ShiftLeft/ShiftLeft_6.h"
#include "ShiftLeft/ShiftLeft_7.h"

#include "ShiftRight/ShiftRight_0.h"
#include "ShiftRight/ShiftRight_1.h"
#include "ShiftRight/ShiftRight_2.h"
#include "ShiftRight/ShiftRight_3.h"
#include "ShiftRight/ShiftRight_4.h"
#include "ShiftRight/ShiftRight_5.h"
#include "ShiftRight/ShiftRight_6.h"
#include "ShiftRight/ShiftRight_7.h"

namespace Sprites
{

    constexpr const uint8_t *Happy[] =
        {
            Happy_0,
            Happy_1,
            Happy_2,
            Happy_3,
            Happy_4,
            Happy_5,
            Happy_6,
            Happy_7};

    constexpr size_t HappyCount = sizeof(Happy) / sizeof(Happy[0]);

    constexpr const uint8_t *Angry[] =
        {
            Angry_0,
            Angry_1,
            Angry_2,
            Angry_3,
            Angry_4,
            Angry_5,
            Angry_6,
            Angry_7};

    constexpr size_t AngryCount = sizeof(Angry) / sizeof(Angry[0]);

    constexpr const uint8_t *Dizzy[] =
        {
            Dizzy_0,
            Dizzy_1,
            Dizzy_2,
            Dizzy_3,
            Dizzy_4,
            Dizzy_5,
            Dizzy_6,
            Dizzy_7};

    constexpr size_t DizzyCount = sizeof(Dizzy) / sizeof(Dizzy[0]);

    constexpr const uint8_t *Blink[] =
        {
            Blink_0,
            Blink_1,
            Blink_2,
            Blink_3,
            Blink_4,
            Blink_5,
            Blink_6,
            Blink_7};

    constexpr size_t BlinkCount = sizeof(Blink) / sizeof(Blink[0]);

    constexpr const uint8_t *Sleep[] =
        {
            Sleep_0,
            Sleep_1,
            Sleep_2,
            Sleep_3,
            Sleep_4,
            Sleep_5,
            Sleep_6,
            Sleep_7};

    constexpr size_t SleepCount = sizeof(Sleep) / sizeof(Sleep[0]);

    constexpr const uint8_t *Surprise[] =
        {
            Surprise_0,
            Surprise_1,
            Surprise_2,
            Surprise_3,
            Surprise_4,
            Surprise_5,
            Surprise_6,
            Surprise_7};

    constexpr size_t SurpriseCount = sizeof(Surprise) / sizeof(Surprise[0]);

    constexpr const uint8_t *ShiftLeft[] =
        {
            ShiftLeft_0,
            ShiftLeft_1,
            ShiftLeft_2,
            ShiftLeft_3,
            ShiftLeft_4,
            ShiftLeft_5,
            ShiftLeft_6,
            ShiftLeft_7};

    constexpr size_t ShiftLeftCount = sizeof(ShiftLeft) / sizeof(ShiftLeft[0]);
    
    constexpr const uint8_t *ShiftRight[] =
        {
            ShiftRight_0,
            ShiftRight_1,
            ShiftRight_2,
            ShiftRight_3,
            ShiftRight_4,
            ShiftRight_5,
            ShiftRight_6,
            ShiftRight_7};

    constexpr size_t ShiftRightCount = sizeof(ShiftRight) / sizeof(ShiftRight[0]);
}
