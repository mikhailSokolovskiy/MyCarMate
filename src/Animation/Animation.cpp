#include "Animation.h"

void Animation::SetFrameCount(size_t frameCount)
{
    m_frameCount = frameCount;
    m_currentFrame = 0;
}

void Animation::Update()
{
    if (m_frameCount == 0)
    {
        return;
    }

    m_currentFrame++;

    if (m_currentFrame >= m_frameCount)
    {
        m_currentFrame = 0;
    }
}

size_t Animation::GetCurrentFrame() const { return m_currentFrame; }
