#include <Arduino.h>

#include "App.h"

void App::Setup()
{
    m_display.SetSpriteManager(&m_spriteManager);
    m_display.Init();
}

void App::Load()
{
    m_spriteManager.LoadSprites();
    m_display.ShowSprite(Emotion::Default, 0);
}

void App::Update()
{
    if (Serial.available())
    {
        const char command = Serial.read();

        if (command == '1')
        {
            SetEmotion(Emotion::Happy);
        }
        else if (command == '2')
        {
            SetEmotion(Emotion::Angry);
        }
        else if (command == '3')
        {
            SetEmotion(Emotion::Blink);
        }
        else if (command == '4')
        {
            SetEmotion(Emotion::Surprise);
        }
    }

    m_animation.Update();
    m_display.Update();

    if (m_currentEmotion != Emotion::Default && m_animation.IsFinished())
    {
        SetEmotion(Emotion::Default);

        m_display.ShowSprite(
            Emotion::Default,
            0);

        return;
    }

    if (m_animation.IsFrameChanged())
    {
        m_display.ShowSprite(
            m_currentEmotion,
            m_animation.GetCurrentFrame());
    }
}

void App::SetEmotion(Emotion emotion)
{
    m_currentEmotion = emotion;

    if (emotion == Emotion::Default)
    {
        return;
    }

    m_animation.SetFrameCount(
        m_spriteManager.GetFrameCount(emotion));
}