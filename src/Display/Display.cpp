#include <Arduino.h>

#include "Display.h"
#include <Constants/DisplayConfig.h>
#include <Constants/SpriteConfig.h>

void Display::Init()
{
    m_lgfx.init();
    m_lgfx.fillScreen(TFT_BLACK);

    Serial.println("Display initialized");

    m_spriteManager.Init();
}

void Display::Update()
{
}

void Display::Load()
{
    m_spriteManager.LoadSprites();
}

void Display::ShowSprite(Emotion emotion, size_t frame)
{
    const Sprite *sprite = m_spriteManager.Get(emotion, frame);

    if (sprite == nullptr)
    {
        return;
    }

    m_lgfx.fillScreen(TFT_BLACK);

    DrawBitmap(
        sprite->GetPixels(),
        sprite->GetWidth(),
        sprite->GetHeight());
}

void Display::DrawBitmap(
    const uint8_t *data,
    uint16_t width,
    uint16_t height)
{
    const uint16_t scaledWidth =
        width * SpriteConstants::Scale;

    const uint16_t scaledHeight =
        height * SpriteConstants::Scale;

    const uint16_t x =
        (DisplayConstants::Width - scaledWidth) / 2;

    const uint16_t y =
        (DisplayConstants::Height - scaledHeight) / 2;

    for (uint16_t py = 0; py < height; py++)
    {
        uint8_t row = data[py];

        for (uint16_t px = 0; px < width; px++)
        {
            if (row & (1 << (7 - px)))
            {
                m_lgfx.fillRect(
                    x + px * SpriteConstants::Scale,
                    y + py * SpriteConstants::Scale,
                    SpriteConstants::Scale,
                    SpriteConstants::Scale,
                    TFT_RED);
            }
        }
    }
}