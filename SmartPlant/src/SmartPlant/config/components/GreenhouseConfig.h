#pragma once

#include "../SmartPlantConfig.h"

#ifdef GREENHOUSE

#include "../../library/AnalogSensor.h"
#include "../../components/Greenhouse.h"
#include "../../library/VisualizationUtils.h"

// ----- Broker settings -----

const char* BROKER_TOPIC = "SmartPlant/Greenhouse/TestGreenhouse";
const char* BROKER_TOPIC_WEATHER = "SmartPlant/WeatherData/Zürich";


// ----- General configuration -----

const AnalogSensorConfig CO2_ANALOG_SENSOR_CONFIG = AnalogSensorConfig{0, 100, 0.0f, 50.0f};
const AnalogSensorConfig TEMP_INSIDE_SENSOR_CONFIG = AnalogSensorConfig{0, 1024, -50.0f, 100.0f};

Greenhouse::GreenhouseConfig GREENHOUSE_CONFIG = Greenhouse::GreenhouseConfig
{
    20.0f, 15.0f, // CO2 level (min / critical)
    20.0f, 30.0f // optimal temperature (min / max)
};


// ----- Visualisation settings -----

enum VisualizationLED
{
    CO2_LEVEL = 0,
    TEMPERATURE_INSIDE = 1,
    TEMPERATURE_OUTSIDE = 2,
    WINDOW_OPEN = 3,
    WINDOW_CLOSED = 4,
    IS_RAINING = 5,
    ADDING_CO2 = 6,
    OPEN_WINDOW = 7,
    CLOSE_WINDO = 8
};

void visualizeGreenhouse(LED& leds, Greenhouse::GreenhouseSignals& signals)
{
  setLEDColor(leds, VisualizationLED::CO2_LEVEL, RGBColor(signals.co2LevelSensor.getSingal(),signals.co2LevelSensor.getMinSignal(), signals.co2LevelSensor.getMaxSignal()));
  setLEDColor(leds, VisualizationLED::TEMPERATURE_INSIDE, RGBColor(signals.tempInsideSensor.getSingal(), signals.tempInsideSensor.getMinSignal(), signals.tempInsideSensor.getMaxSignal()));
  setLEDColor(leds, VisualizationLED::TEMPERATURE_OUTSIDE, RGBColor(signals.tempOutside, -40.0f, 100.0f));
  setLEDColor(leds, VisualizationLED::WINDOW_OPEN, RGBColor(signals.DI_WindowOpen));
  setLEDColor(leds, VisualizationLED::WINDOW_CLOSED, RGBColor(signals.DI_WindowClosed));
  setLEDColor(leds, VisualizationLED::IS_RAINING, RGBColor(signals.IsRaining));

  setLEDColor(leds, VisualizationLED::ADDING_CO2, RGBColor(signals.DO_AddingCO2));
  setLEDColor(leds, VisualizationLED::OPEN_WINDOW, RGBColor(signals.DO_OpenWindow));
  setLEDColor(leds, VisualizationLED::CLOSE_WINDO, RGBColor(signals.DO_CloseWindow));
}

#endif