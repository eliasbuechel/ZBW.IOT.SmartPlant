#include "VisualizationUtils.h"

RGBColor::RGBColor(bool value)
{
    R = value ? 255 : 0;

}

RGBColor::RGBColor(const unsigned int value, unsigned int lowerBound, unsigned int upperBound)
{
    // Convert the input value to a range from 0 to 1
    unsigned int range = upperBound - lowerBound;
    float normalized_value = (value - lowerBound) / (float)range;

    // Calculate the corresponding RGB values
    R = (uint8_t)(255 * normalized_value);
    B = (uint8_t)(255 * (1 - normalized_value));
}

RGBColor::RGBColor(const float value, float lowerBound, float upperBound)
{
    // Convert the input value to a range from 0 to 1
    float range = upperBound - lowerBound;
    float normalized_value = (value - lowerBound) / range;

    // Calculate the corresponding RGB values
    R = (uint8_t)(255 * normalized_value);
    B = (uint8_t)(255 * (1 - normalized_value));
}

void setLEDColor(LED& leds, uint8_t index, RGBColor color)
{
  leds.setLEDColor(index, color.R, color.G, color.B);
}