#include "SmartPlant.h"

bool SmartPlant::execute(LED& leds)
{
    SmartPlant::Greenhouse_Test::execute(leds);
    
    return true;
}