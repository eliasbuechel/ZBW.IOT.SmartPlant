#pragma once

#include "Greenhouse.h"

#include "../config/components/GreenhouseConfig.h"
#include "../simulation/GreenhouseSimulation.h"

namespace Greenhouse
{
    // inputs
    unsigned int AI_CO2Level;
    unsigned int AI_TempInside;
    float TempOutside;
    bool DI_WindowOpen;
    bool DI_WindowClosed;
    bool IsRaining;

    // outputs
    bool DO_AddingCO2;
    bool DO_OpenWindow;
    bool DO_CloseWindow;


    AnalogSensor co2LevelSensor = AnalogSensor(AI_CO2Level, CO2_ANALOG_SENSOR_CONFIG);
    AnalogSensor tempInsideSensor = AnalogSensor(AI_TempInside, TEMP_INSIDE_SENSOR_CONFIG);

    

    GreenhouseSignals greenhouseSignals = GreenhouseSignals
    {
        co2LevelSensor, tempInsideSensor, TempOutside,
        DI_WindowOpen, DI_WindowClosed, IsRaining,
        DO_AddingCO2, DO_OpenWindow, DO_CloseWindow
    };

    Greenhouse greenhouse = Greenhouse(GREENHOUSE_CONFIG, greenhouseSignals, BROKER_TOPIC, BROKER_TOPIC_WEATHER);
    GreenhouseSimulation simulation = GreenhouseSimulation(greenhouseSignals);

    bool configure()
    {
        greenhouse.configure();

        return true;
    }

    bool execute(LED& leds, QwiicButton& button)
    {
        greenhouse.execute();
        simulation.execute(button);
        visualizeGreenhouse(leds, greenhouseSignals);

        return true;
    }
}