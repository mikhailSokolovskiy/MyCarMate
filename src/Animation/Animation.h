#pragma once

#include <cstddef>

class Animation
{

public:
    void SetFrameCount(size_t frameCount);
    void Update();

    size_t GetCurrentFrame() const;

private:
    size_t m_frameCount = 0;
    size_t m_currentFrame = 0;
};