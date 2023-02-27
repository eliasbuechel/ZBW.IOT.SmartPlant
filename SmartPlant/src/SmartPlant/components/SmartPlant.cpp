#include "SmartPlant.h"

#include "WeatherData.h"

bool SmartPlant::configure()
{
    SmartPlant::Greenhouse_Test::configure();

    return true;
}

bool SmartPlant::execute(LED& leds)
{
    WetherData::execute();
    SmartPlant::Greenhouse_Test::execute(leds);
    
    return true;
}