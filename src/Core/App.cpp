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
    m_display.ShowSprite(Emotion::Happy, 0);
}