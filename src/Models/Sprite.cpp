#include "Sprite.h"

Sprite::Sprite(uint16_t width, uint16_t height, const uint16_t *pixels)
{
    m_width = width;
    m_height = height;
    m_pixels = pixels;
}

uint16_t Sprite::GetWidth() const
{
    return m_width;
}

uint16_t Sprite::GetHeight() const
{
    return m_height;
}

const uint16_t* Sprite::GetPixels() const
{
    return m_pixels;
}