#pragma once

#include "LGFX_Config.h"
#include "SpriteManager.h"

class Display
{
public:
    void Init();
    void Load();
    void Update();
    void ShowSprite(Emotion emotion, size_t frame);

private:
    void DrawBitmap(
        const uint8_t *data,
        uint16_t width,
        uint16_t height);

    LGFX m_lgfx;
    SpriteManager m_spriteManager;
};