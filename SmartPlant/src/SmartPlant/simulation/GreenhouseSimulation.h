#pragma once

#include "AnalogSignalSimulator.h"
#include "WindowSimulator.h"
#include "RainSimulator.h"

#include "../components/Greenhouse.h"

namespace Greenhouse
{
    class GreenhouseSimulation
    {
    public:
        GreenhouseSimulation(GreenhouseSignals& signals);
        bool execute();

    private:
        AnalogSignalSimulator m_Co2LevelSimulator;
        AnalogSignalSimulator m_TempInsideSimulator;

        WindowSimulator m_WindowSimulator;
        BoolSimulator m_RainSimulator;
    };
}