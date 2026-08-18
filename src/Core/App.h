#pragma once

#include "../Display/Display.h"
#include "../Animation/Animation.h"
#include "../Display/SpriteManager.h"
#include <Trigger/TriggerService.h>

class App
{
public:
    void Setup();
    void Load();
    void Update();
    void SetEmotion(Emotion emotion);

private:
    SpriteManager m_spriteManager;
    Display m_display;
    Animation m_animation;
    TriggerService m_triggerService;

    Emotion m_currentEmotion = Emotion::Default;
};