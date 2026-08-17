#pragma once

#include "../Display/Display.h"
#include "../Animation/Animation.h"
#include "../Display/SpriteManager.h"

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

    Emotion m_currentEmotion = Emotion::Default;
};