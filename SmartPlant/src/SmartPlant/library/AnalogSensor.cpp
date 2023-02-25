#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(const unsigned int& signal, const AnalogSensorConfig& config)
    : c_Signal(signal), c_Config(config)
    {}

bool AnalogSensor::execute()
{ 
    float normalized = (float)(c_Signal - c_Config.MIN_SIGNAL) / (float)(c_Config.MAX_SIGNAL - c_Config.MIN_SIGNAL);
    m_Value = normalized * (c_Config.MAX_VALUE - c_Config.MIN_VALUE) + c_Config.MIN_VALUE;
    
    return true;
}
float AnalogSensor::getValue() const
{
    return m_Value;
}

const unsigned int AnalogSensor::getMinSignal()
{
    return c_Config.MIN_SIGNAL;
}

const unsigned int AnalogSensor::getMaxSignal()
{
    return c_Config.MAX_SIGNAL;
}

const unsigned int& AnalogSensor::getSingal()
{
    return c_Signal;
}