#include "SmartPlant.h"

#include "../config/SmartPlantConfig.h"

#ifdef GREENHOUSE

#include "GreenhouseComponent.h"

#endif

#ifdef WEATHER_DATA
    #include "WeatherData.h"
#endif

bool SmartPlant::configure()
{
    #ifdef GREENHOUSE
        Greenhouse::configure();
    #endif
    #ifdef WEATHER_DATA
    #endif

    return true;
}

bool SmartPlant::execute(LED& leds, QwiicButton& button)
{
    #ifdef GREENHOUSE
        Greenhouse::execute(leds, button);
    #endif
    #ifdef WEATHER_DATA
        WetherData::execute();
    #endif
    
    return true;
}