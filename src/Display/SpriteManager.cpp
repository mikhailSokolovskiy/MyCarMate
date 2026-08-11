#include "SpriteManager.h"

#include <Constants/SpriteConfig.h>
#include <Assets/Sprites/Happy/Happy.h>

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

    for (size_t i = 0; i < HappyFrameCount; i++)
    {
        happy.sprites.emplace_back(
            SpriteConstants::Width,
            SpriteConstants::Height,
            HappyFrames[i]);
    }

    m_emotions.push_back(happy);
}
