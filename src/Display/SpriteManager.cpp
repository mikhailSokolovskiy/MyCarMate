#include "SpriteManager.h"

#include <Assets/Sprites/Happy/Happy.h>
#include <Constants/SpriteConfig.h>
#include <Assets/Sprites/Default/Default_0.h>

void SpriteManager::LoadSprites()
{
    m_emotions.clear();

    LoadDefault();
    LoadHappy();
}

void SpriteManager::LoadDefault()
{
    EmotionSprites defaultEmotion;

    defaultEmotion.emotion = Emotion::Default;

    defaultEmotion.sprites.emplace_back(
        SpriteConstants::Width,
        SpriteConstants::Height,
        Default_0);

    m_emotions.push_back(defaultEmotion);
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

const Sprite *SpriteManager::Get(
    Emotion emotion,
    size_t frame)
{
    for (auto &emotionSprites : m_emotions)
    {
        if (emotionSprites.emotion != emotion)
        {
            continue;
        }

        if (frame >= emotionSprites.sprites.size())
        {
            return nullptr;
        }

        return &emotionSprites.sprites[frame];
    }

    return nullptr;
}

size_t SpriteManager::GetFrameCount(Emotion emotion)
{
    for (const auto &emotionSprites : m_emotions)
    {
        if (emotionSprites.emotion == emotion)
        {
            return emotionSprites.sprites.size();
        }
    }

    return 0;
}