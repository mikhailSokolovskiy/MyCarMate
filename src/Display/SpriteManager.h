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
    void Init();

    void LoadSprites();

    void UnloadSprites();

private:
    std::vector<EmotionSprites> m_emotions;
};