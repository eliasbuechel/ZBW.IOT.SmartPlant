#include "GreenhouseSimulation.h"

Greenhouse::GreenhouseSimulation::GreenhouseSimulation(GreenhouseSignals& signals)
    : m_Co2LevelSimulator(AnalogSignalSimulator(signals.co2LevelSensor)),
      m_TempInsideSimulator(AnalogSignalSimulator(signals.tempInsideSensor)),
      m_TempOutsideSimulator(AnalogSignalSimulator(signals.tempOutsideSensor)),
      m_WindowSimulator(WindowSimulator((bool&)signals.DI_WindowOpen, (bool&)signals.DI_WindowClosed, signals.DO_OpenWindow, signals.DO_CloseWindow)),
      m_RainSimulator(BoolSimulator((bool&)(signals.DI_IsRaining), 3000, 10000))
{}

bool Greenhouse::GreenhouseSimulation::execute()
{
    m_Co2LevelSimulator.execute();
    m_TempInsideSimulator.execute();
    m_TempOutsideSimulator.execute();
    m_WindowSimulator.execute();
    m_RainSimulator.execute();

    return true;
}