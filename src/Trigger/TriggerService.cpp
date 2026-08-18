#include <Arduino.h>

#include "TriggerService.h"

void TriggerService::Init()
{
}

bool TriggerService::Update(Emotion &emotion)
{
    if (!Serial.available())
    {
        return false;
    }

    const char command = Serial.read();

    switch (command)
    {
    case '1':
        emotion = Emotion::Happy;
        return true;

    case '2':
        emotion = Emotion::Angry;
        return true;

    case '3':
        emotion = Emotion::Dizzy;
        return true;

    case '4':
        emotion = Emotion::Sleep;
        return true;

    case '5':
        emotion = Emotion::Blink;
        return true;

    case '6':
        emotion = Emotion::Surprise;
        return true;

    case '7':
        emotion = Emotion::ShiftLeft;
        return true;

    case '8':
        emotion = Emotion::ShiftRight;
        return true;
    }

    return false;
}