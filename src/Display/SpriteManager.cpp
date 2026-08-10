#include "SpriteManager.h"

#include <Assets/Sprites/Happy/Happy_0.h>
#include <Constants/SpriteConfig.h>

void SpriteManager::Init()
{
}

void SpriteManager::LoadSprites()
{
    m_emotions.clear();

    LoadHappy();
}

Sprite *EmotionSprites::GetFrame(size_t frame)
{
    if (frame >= sprites.size())
    {
        return nullptr;
    }

    return &sprites[frame];
}

void EmotionSprites::AddFrame(
    uint16_t width,
    uint16_t height,
    const uint8_t *pixels)
{
    sprites.emplace_back(width, height, pixels);
}

const Sprite *SpriteManager::Get(Emotion emotion, size_t frame)
{
    for (auto &emotionSprites : m_emotions)
    {
        if (emotionSprites.emotion == emotion)
        {
            if (frame >= emotionSprites.sprites.size())
            {
                return nullptr;
            }

            return &emotionSprites.sprites[frame];
        }
    }

    return nullptr;
}

void SpriteManager::LoadHappy()
{
    EmotionSprites happy;
    happy.emotion = Emotion::Happy;

    happy.sprites.emplace_back(
        SpriteConstants::Width,
        SpriteConstants::Height,
        Happy_0);

    m_emotions.push_back(happy);
}
