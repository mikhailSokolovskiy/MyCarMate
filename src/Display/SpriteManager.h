#pragma once

#include <vector>

#include <Models/Emotion.h>
#include <Models/Sprite.h>

struct EmotionSprites
{
    Emotion emotion;
    std::vector<Sprite> sprites;
};

class SpriteManager
{
public:
    void LoadSprites();

    const Sprite *Get(
        Emotion emotion,
        size_t frame);

    size_t GetFrameCount(Emotion emotion);

private:
    void LoadDefault();
    void LoadHappy();

    std::vector<EmotionSprites> m_emotions;
};