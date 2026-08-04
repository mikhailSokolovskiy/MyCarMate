#pragma once

#include "LGFX_Config.h"
#include "SpriteManager.h"

class Display
{
public:
    void Init();
    void Load();
    void Update();

private:
    LGFX m_lgfx;
    SpriteManager m_spriteManager;
};