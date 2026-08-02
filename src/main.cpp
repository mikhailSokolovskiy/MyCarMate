#include <Arduino.h>

#include "Core/App.h"

App app;

void setup()
{
    Serial.begin(115200);
    delay(6000);
    app.Setup();
}

void loop()
{
    app.Update();
}