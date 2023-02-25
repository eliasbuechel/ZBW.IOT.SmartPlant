#pragma once

#include <iostream>
#include <fsm.h>

#include "WindowCtrl.h"
#include "../library/AnalogSensor.h"




namespace Greenhouse
{
    enum CO2Condition
    {
        OK = 0, MIN, CRITICAL
    };

    struct GreenhouseConfig
    {
        const float MIN_CO2_LEVEL;
        const float CRITICAL_CO2_LEVEL;
        const float MIN_OPTIMAL_TEMP;
        const float MAX_OPTIMAL_TEMP;
    };

    struct GreenhouseSignals
    {
        // analog inputs
        AnalogSensor& co2LevelSensor;
        AnalogSensor& tempInsideSensor;
        AnalogSensor& tempOutsideSensor;

        // digital inputs
        const bool& DI_WindowOpen;
        const bool& DI_WindowClosed;
        const bool& DI_IsRaining;

        // digital outputs
        bool& DO_AddingCO2;
        bool& DO_OpenWindow;
        bool& DO_CloseWindow;
    };

    class Greenhouse
    {
    public:
        Greenhouse(const GreenhouseConfig& config, GreenhouseSignals& signals);
        bool execute();
    
    private:
        bool evaluateTemperationNeccesary(const AnalogSensor& tempInsideSensor, const AnalogSensor& tempOutsideSensor) const;
        void controlCO2Addition(CO2Condition co2Condition);
        void controlVentilation(CO2Condition co2Condition, bool isTemperationNeccesary);
        CO2Condition getCO2Condition(const AnalogSensor& co2LevelSensor) const;

    private:
        const GreenhouseConfig& c_Config;
        GreenhouseSignals& m_Signals;
        
        WindowCtrl* m_WindowCtrl;
        WindowSignals m_WindowSignals;
    };
}