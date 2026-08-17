#pragma once

#include <cstddef>

class Animation
{
public:
    void SetFrameCount(size_t frameCount);
    void SetFrameInterval(unsigned long interval);
    void Update();

    size_t GetCurrentFrame() const;
    bool IsFinished() const;
    bool IsFrameChanged() const;

private:
    size_t m_frameCount = 0;
    size_t m_currentFrame = 0;

    unsigned long m_frameInterval = 100;
    unsigned long m_lastFrameTime = 0;

    bool m_finished = false;
    bool m_frameChanged = false;
};