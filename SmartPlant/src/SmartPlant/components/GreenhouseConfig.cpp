#include "SmartPlant.h"

#include "Greenhouse.h"
#include "../simulation/GreenhouseSimulation.h"
#include "../library/VisualizationUtils.h"

using namespace SmartPlant::Greenhouse_Test;

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


const AnalogSensorConfig co2LevelSensorConfig = AnalogSensorConfig{0, 100, 0.0f, 50.0f};
const AnalogSensorConfig tempInsideSensorConfig = AnalogSensorConfig{0, 1024, -50.0f, 100.0f};

AnalogSensor co2LevelSensor = AnalogSensor(AI_CO2Level, co2LevelSensorConfig);
AnalogSensor tempInsideSensor = AnalogSensor(AI_TempInside, tempInsideSensorConfig);


const Greenhouse::GreenhouseConfig greenhouseConfig = Greenhouse::GreenhouseConfig
{
    20.0f, 15.0f, // CO2 level (min / critical)
    20.0f, 30.0f // optimal temperature (min / max)
};

Greenhouse::GreenhouseSignals greenhouseSignals = Greenhouse::GreenhouseSignals
{
    co2LevelSensor, tempInsideSensor, TempOutside,
    DI_WindowOpen, DI_WindowClosed, IsRaining,
    DO_AddingCO2, DO_OpenWindow, DO_CloseWindow
};

Greenhouse::Greenhouse greenhouse = Greenhouse::Greenhouse(greenhouseConfig, greenhouseSignals);
Greenhouse::GreenhouseSimulation simulation = Greenhouse::GreenhouseSimulation(greenhouseSignals);

static void visualize(LED& leds);

bool SmartPlant::Greenhouse_Test::configure()
{
  greenhouse.configure();

  return true;
}

bool SmartPlant::Greenhouse_Test::execute(LED& leds)
{
  greenhouse.execute();
  simulation.execute();
  visualize(leds);

  return true;
}

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

static void visualize(LED& leds)
{
  // Serial.println(std::to_string(AI_CO2Level).c_str());
  // Serial.println(std::to_string(AI_TempInside).c_str());
  //Serial.println(std::to_string(TempOutside).c_str());
  // Serial.println(std::to_string(DI_WindowOpen).c_str());
  // Serial.println(std::to_string(DI_WindowClosed).c_str());
  // Serial.println(std::to_string(DI_IsRaining).c_str());

  // Serial.println(std::to_string(DO_AddingCO2).c_str());
  // Serial.println(std::to_string(DO_OpenWindow).c_str());
  // Serial.println(std::to_string(DO_CloseWindow).c_str());

  // setLEDColor(leds, VisualizationLED::CO2_LEVEL, RGBColor(AI_CO2Level, co2LevelSensorConfig.MIN_SIGNAL, co2LevelSensorConfig.MAX_SIGNAL));
  // setLEDColor(leds, VisualizationLED::TEMPERATURE_INSIDE, RGBColor(AI_TempInside, tempInsideSensorConfig.MIN_SIGNAL, tempInsideSensorConfig.MAX_SIGNAL));
  // setLEDColor(leds, VisualizationLED::TEMPERATURE_OUTSIDE, RGBColor(AI_TempOutside,  tempOutsideSensorConfig.MIN_SIGNAL, tempOutsideSensorConfig.MAX_SIGNAL));
  // setLEDColor(leds, VisualizationLED::WINDOW_OPEN, RGBColor(DI_WindowOpen));
  // setLEDColor(leds, VisualizationLED::WINDOW_CLOSED, RGBColor(DI_WindowClosed));
  setLEDColor(leds, VisualizationLED::IS_RAINING, RGBColor(IsRaining));

  // setLEDColor(leds, VisualizationLED::ADDING_CO2, RGBColor(DO_AddingCO2));
  // setLEDColor(leds, VisualizationLED::OPEN_WINDOW, RGBColor(DO_OpenWindow));
  // setLEDColor(leds, VisualizationLED::CLOSE_WINDO, RGBColor(DO_CloseWindow));
}