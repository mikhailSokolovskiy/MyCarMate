#pragma once

#include <cstdint>

class Sprite
{
public:
    Sprite(uint16_t width, uint16_t height, const uint16_t *pixels);

private:
    uint16_t m_width;
    uint16_t m_height;
    const uint16_t *m_pixels;

    uint16_t GetWidth() const;
    uint16_t GetHeight() const;
    const uint16_t *GetPixels() const;
};