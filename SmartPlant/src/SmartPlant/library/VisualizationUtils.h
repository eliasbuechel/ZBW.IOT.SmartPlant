#pragma once

#include <QwiicLedStick.h>

struct RGBColor
{
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;

    RGBColor(bool value);
    RGBColor(const unsigned int value, unsigned int lowerBound, unsigned int upperBound);
};

void setLEDColor(LED& leds, uint8_t index, RGBColor color);