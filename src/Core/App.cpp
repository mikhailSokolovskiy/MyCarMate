#include <Arduino.h>

#include "App.h"

void App::Setup()
{
    Serial.println("Application initialized");

    m_display.Init();
}

void App::Update()
{
    m_display.Update();

    if (millis() - m_lastUpdate >= 1000)
    {
        m_lastUpdate = millis();

        Serial.println("Update");
    }
}