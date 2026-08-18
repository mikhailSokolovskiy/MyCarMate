#include "SpriteManager.h"

#include <Assets/Sprites/SpriteList.h>
#include <Constants/SpriteConfig.h>
#include <Assets/Sprites/Default/Default_0.h>

void SpriteManager::LoadSprites()
{
    m_emotions.clear();

    LoadDefault();

    LoadEmotionSet(Emotion::Happy, Sprites::Happy, Sprites::HappyCount);
    LoadEmotionSet(Emotion::Angry, Sprites::Angry, Sprites::AngryCount);
    LoadEmotionSet(Emotion::Dizzy, Sprites::Dizzy, Sprites::DizzyCount);
    LoadEmotionSet(Emotion::Blink, Sprites::Blink, Sprites::BlinkCount);
    LoadEmotionSet(Emotion::Sleep, Sprites::Sleep, Sprites::SleepCount);
    LoadEmotionSet(Emotion::Surprise, Sprites::Surprise, Sprites::SurpriseCount);
    LoadEmotionSet(Emotion::ShiftLeft, Sprites::ShiftLeft, Sprites::ShiftLeftCount);
    LoadEmotionSet(Emotion::ShiftRight, Sprites::ShiftRight, Sprites::ShiftRightCount);
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

void SpriteManager::LoadEmotionSet(Emotion emotion, const uint8_t *const *frames, size_t count)
{
    EmotionSprites emotionSprites;
    emotionSprites.emotion = emotion;

    for (size_t i = 0; i < count; i++)
    {
        emotionSprites.sprites.emplace_back(
            SpriteConstants::Width,
            SpriteConstants::Height,
            frames[i]);
    }

    m_emotions.push_back(emotionSprites);
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