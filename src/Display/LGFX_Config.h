#pragma once

#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
public:
    LGFX();

private:
    lgfx::Panel_ST7789 _panel;
    lgfx::Bus_SPI _bus;
};