#include "SpriteManager.h"

#include <Assets/Sprites/Happy/Happy_0.h>

void SpriteManager::Init()
{
}

void SpriteManager::LoadSprites()
{
    m_emotions.clear();

    EmotionSprites happy;
    happy.emotion = Emotion::Happy;

    Sprite happyFrame(
        8,
        8,
        Happy_0
    );

    happy.sprites.push_back(happyFrame);

    m_emotions.push_back(happy);
}

Sprite *EmotionSprites::GetFrame(size_t frame)
{
    if (frame >= sprites.size())
    {
        return nullptr;
    }

    return &sprites[frame];
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