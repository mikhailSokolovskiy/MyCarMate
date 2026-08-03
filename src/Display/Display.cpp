#include <Arduino.h>

#include "Display.h"

void Display::Init()
{
    Serial.println("Display initialized");

    m_lgfx.init();

    m_lgfx.setRotation(0);

    m_lgfx.fillScreen(TFT_BLACK);

    m_lgfx.setTextColor(TFT_GREEN);
    m_lgfx.setTextSize(2);
    m_lgfx.drawString("Hello im frend!", 20, 20);
}

void Display::Update()
{
}