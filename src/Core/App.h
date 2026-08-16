#pragma once

#include "../Display/Display.h"
#include "../Animation/Animation.h"


class App
{
public:
    void Setup();
    void Load();
    void Update();

private:
    Display m_display;
    Animation m_animation;

    size_t m_frame = 0;
    unsigned long m_lastFrameTime = 0;
};