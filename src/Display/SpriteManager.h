#pragma once

#include <vector>
#include <Models/Emotion.h>
#include <Models/Sprite.h>

struct EmotionSprites
{
    Emotion emotion;
    std::vector<Sprite> sprites;
    Sprite *GetFrame(size_t frame);
    void AddFrame(uint16_t width, uint16_t height, const uint8_t *pixels);
};

class SpriteManager
{

public:
    void Init();
    void LoadSprites();
    void UnloadSprites();
    const Sprite *Get(Emotion emotion, size_t frame);

private:
    void LoadHappy();
    
    std::vector<EmotionSprites> m_emotions;
};