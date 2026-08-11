#include <Arduino.h>

#include "App.h"

void App::Setup()
{
    Serial.println("Application initialized");

    m_display.Init();
}

void App::Load()
{
    m_display.Load();
}

void App::Update()
{
    m_display.Update();

    if (millis() - m_lastFrameTime >= 300)
    {
        m_lastFrameTime = millis();

        m_display.ShowSprite(Emotion::Happy, m_frame);

        m_frame++;

        if (m_frame >= 4)
        {
            m_frame = 0;
            delay(800);
        }
    }
}