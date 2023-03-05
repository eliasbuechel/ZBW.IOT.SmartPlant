#include "GreenhouseSimulation.h"

Greenhouse::GreenhouseSimulation::GreenhouseSimulation(GreenhouseSignals& signals)
    : m_Co2LevelSimulator(AnalogSignalSimulator(signals.co2LevelSensor)),
      m_TempInsideSimulator(AnalogSignalSimulator(signals.tempInsideSensor)),
      m_WindowSimulator(WindowSimulator((bool&)signals.DI_WindowOpen, (bool&)signals.DI_WindowClosed, signals.DO_OpenWindow, signals.DO_CloseWindow)),
      m_RainSimulator(BoolSimulator((bool&)(signals.IsRaining), 3000, 10000)),
      m_IsRainingSignal(signals.IsRaining)
{}

bool Greenhouse::GreenhouseSimulation::execute(QwiicButton& button)
{
    m_Co2LevelSimulator.execute();
    m_TempInsideSimulator.execute();
    m_WindowSimulator.execute();
    // m_RainSimulator.execute();
    executeButtonRainSimulation(button);

    return true;
}

bool Greenhouse::GreenhouseSimulation::executeButtonRainSimulation(QwiicButton& button)
{
    bool buttonState = button.isPressed();
    if (m_IsRainingSignal != buttonState)
        m_IsRainingSignal = buttonState;
    
    return true;
}