#include "LGFX_Config.h"

#include "Constants/Pins.h"

LGFX::LGFX()
{
    {
        auto cfg = _bus.config();

        cfg.spi_host = SPI2_HOST;

        cfg.spi_mode = 3;

        cfg.pin_sclk = Pins::DisplaySCK;
        cfg.pin_mosi = Pins::DisplayMOSI;
        cfg.pin_miso = -1;
        cfg.pin_dc = Pins::DisplayDC;

        cfg.freq_write = 40000000;
        cfg.freq_read = 16000000;

        _bus.config(cfg);
    }

    {
        auto cfg = _panel.config();

        cfg.pin_cs = -1;
        cfg.pin_rst = Pins::DisplayRST;

        cfg.panel_width = 240;
        cfg.panel_height = 240;

        cfg.memory_width = 240;
        cfg.memory_height = 240;

        cfg.invert = true;

        _panel.config(cfg);
    }

    _panel.setBus(&_bus);
    setPanel(&_panel);
}