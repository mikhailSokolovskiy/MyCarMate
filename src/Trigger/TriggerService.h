#pragma once

#include "../Animation/Animation.h"
#include <Models/Emotion.h>

class TriggerService
{
public:
    void Init();
    bool Update(Emotion& emotion);
};