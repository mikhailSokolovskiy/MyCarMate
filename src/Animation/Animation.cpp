#include <Arduino.h>
#include "Animation.h"

void Animation::SetFrameCount(size_t frameCount)
{
    m_frameCount = frameCount;
    m_currentFrame = 0;
    m_lastFrameTime = millis();
    m_finished = false;

    // Новый кадр 0 нужно сразу показать.
    m_frameChanged = true;
}

void Animation::SetFrameInterval(unsigned long interval)
{
    m_frameInterval = interval;
}

void Animation::Update()
{
    m_frameChanged = false;

    if (m_frameCount == 0 || m_finished)
    {
        return;
    }

    const unsigned long currentTime = millis();

    if (currentTime - m_lastFrameTime < m_frameInterval)
    {
        return;
    }

    m_lastFrameTime = currentTime;

    if (m_currentFrame + 1 < m_frameCount)
    {
        m_currentFrame++;
        m_frameChanged = true;
        return;
    }

    m_finished = true;
}

size_t Animation::GetCurrentFrame() const
{
    return m_currentFrame;
}

bool Animation::IsFinished() const
{
    return m_finished;
}

bool Animation::IsFrameChanged() const
{
    return m_frameChanged;
}