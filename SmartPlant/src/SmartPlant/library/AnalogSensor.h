#pragma once

#include <iostream>

struct AnalogSensorConfig
{
    const unsigned int MIN_SIGNAL;
    const unsigned int MAX_SIGNAL;
    const float MIN_VALUE;
    const float MAX_VALUE;
};

class AnalogSensor
{
public:
    AnalogSensor(const unsigned int& signal, const AnalogSensorConfig& config);
    bool execute();
    float getValue() const;
    const unsigned int getMinSignal();
    const unsigned int getMaxSignal();
    const unsigned int& getSingal();

private:
    float m_Value = 0.0f;
    const unsigned int& c_Signal;
    const AnalogSensorConfig& c_Config;
};