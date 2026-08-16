#include <Arduino.h>

#include "App.h"

void App::Setup()
{
    m_display.Init();
}

void App::Load()
{
    m_display.Load();

    m_animation.SetFrameCount(8);
}

void App::Update()
{
    m_animation.Update();
    m_display.Update();

    static size_t lastFrame = 999;

    const size_t currentFrame =
        m_animation.GetCurrentFrame();

    if (currentFrame != lastFrame)
    {
        lastFrame = currentFrame;

        m_display.ShowSprite(
            Emotion::Happy,
            currentFrame);
    }
}