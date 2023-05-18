#pragma once


#include <Arduino.h>
#include <Adafruit_SSD1306.h>


#ifndef __COLORSCANNER__DISPLAY__H__
#define __COLORSCANNER__DISPLAY__H__


class OledDisplay
{
    private:
        Adafruit_SSD1306 _display;
        TwoWire *_wire;

    public:
        OledDisplay();
        ~OledDisplay();
        void initDisplay();
        void writeStringToDisplay(String const &text);
        void writeIcontoDisplay();
};


#endif