#pragma once

#include <Sparkfun_Qwiic_Button.h>

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
        bool execute(QwiicButton& button);

    private:
        AnalogSignalSimulator m_Co2LevelSimulator;
        AnalogSignalSimulator m_TempInsideSimulator;

        WindowSimulator m_WindowSimulator;
        BoolSimulator m_RainSimulator;

        bool executeButtonRainSimulation(QwiicButton& button);

        bool& m_IsRainingSignal;
        bool m_ButtonIsRainingState;
    };
}