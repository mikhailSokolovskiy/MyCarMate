#include <Arduino.h>

#include "Display.h"
#include <Constants/DisplayConfig.h>
#include <Constants/SpriteConfig.h>

void Display::Init()
{
    m_lgfx.init();
    m_lgfx.fillScreen(TFT_BLACK);

    m_renderSprite.setColorDepth(16);

    m_renderSprite.createSprite(
        SpriteConstants::Width * DisplayConstants::SpriteScale,
        SpriteConstants::Height * DisplayConstants::SpriteScale);

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
    const Sprite *sprite =
        m_spriteManager.Get(emotion, frame);

    if (sprite == nullptr)
    {
        return;
    }

    const uint16_t scaledWidth =
        sprite->GetWidth() * DisplayConstants::SpriteScale;

    const uint16_t scaledHeight =
        sprite->GetHeight() * DisplayConstants::SpriteScale;

    const uint16_t x =
        (DisplayConstants::Width - scaledWidth) / 2;

    const uint16_t y =
        (DisplayConstants::Height - scaledHeight) / 2;

    m_renderSprite.fillSprite(TFT_BLACK);

    DrawBitmap(
        sprite->GetPixels(),
        sprite->GetWidth(),
        sprite->GetHeight(),
        TFT_ORANGE);

    m_renderSprite.pushSprite(x, y);
}

void Display::DrawBitmap(
    const uint8_t *data,
    uint16_t width,
    uint16_t height,
    uint16_t color)
{
    const uint16_t scale =
        DisplayConstants::SpriteScale;

    const uint16_t bytesPerRow =
        width / 8;

    for (uint16_t py = 0; py < height; py++)
    {
        for (uint16_t px = 0; px < width; px++)
        {
            const uint16_t byteIndex =
                py * bytesPerRow + px / 8;

            const uint8_t bit =
                7 - (px % 8);

            if (data[byteIndex] & (1 << bit))
            {
                m_renderSprite.fillRect(
                    px * scale,
                    py * scale,
                    scale,
                    scale,
                    color);
            }
        }
    }
}