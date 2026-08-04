#pragma once

#include "../Display/Display.h"

class App
{
public:
    void Setup();
    void Load();
    void Update();

private:
    Display m_display;

    unsigned long m_lastUpdate = 0;
};