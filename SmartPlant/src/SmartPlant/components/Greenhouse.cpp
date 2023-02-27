#include "Greenhouse.h"

#include "../library/Communication.h"
#include "WString.h"


Greenhouse::Greenhouse::Greenhouse(const GreenhouseConfig& config, GreenhouseSignals& signals)
    : c_Config(config), m_Signals(signals),
      m_WindowSignals(WindowSignals
                        {
                            m_Signals.DI_WindowOpen,
                            m_Signals.DI_WindowClosed,
                            m_Signals.DO_OpenWindow,
                            m_Signals.DO_CloseWindow
                        })
{
    m_WindowCtrl = new WindowCtrl(m_WindowSignals);
}

bool Greenhouse::Greenhouse::execute()
{
    m_WindowCtrl->execute();

    bool isTemperationNeccesary = evaluateTemperationNeccesary(m_Signals.tempInsideSensor, m_Signals.tempOutside);
    CO2Condition co2Condition = getCO2Condition(m_Signals.co2LevelSensor);
    
    controlCO2Addition(co2Condition);
    controlVentilation(co2Condition, isTemperationNeccesary);
    return true;
}

bool Greenhouse::Greenhouse::evaluateTemperationNeccesary(const AnalogSensor& tempInsideSensor, const float& tempOutside) const
{
    float tempInside = tempInsideSensor.getValue();
    
    if (tempInside < c_Config.MIN_OPTIMAL_TEMP && tempInside > tempOutside)
        return true;
    else if (tempInside > c_Config.MAX_OPTIMAL_TEMP && tempInside > tempOutside)
        return true;

    return false;
}

void Greenhouse::Greenhouse::controlCO2Addition(CO2Condition co2Condition)
{
    bool& do_addingCo2 = m_Signals.DO_AddingCO2;    
    
    if (!do_addingCo2 && co2Condition == CO2Condition::CRITICAL)
    {
        do_addingCo2 = true;
        return;
    }

    if (do_addingCo2 && co2Condition == CO2Condition::OK)
    {
        do_addingCo2 = false;
        return;
    }
}

void Greenhouse::Greenhouse::controlVentilation(CO2Condition co2Condition, const bool isTemperationNeccesary)
{
    if (co2Condition == CO2Condition::CRITICAL)
    {
        m_WindowCtrl->close();
        return;
    }

    if (co2Condition == CO2Condition::MIN || isTemperationNeccesary)
    {
        m_WindowCtrl->open();
        return;
    }

    m_WindowCtrl->close();
}

Greenhouse::CO2Condition Greenhouse::Greenhouse::getCO2Condition(const AnalogSensor& co2LevelSensor) const
{
    float co2Level = co2LevelSensor.getValue();
    
    if (co2Level < c_Config.CRITICAL_CO2_LEVEL)
        return CO2Condition::CRITICAL;

    if (co2Level < c_Config.MIN_CO2_LEVEL)
        return CO2Condition::MIN;

    return CO2Condition::OK;
}

void Greenhouse::Greenhouse::onCurrentTemperatureHandler(void *context, const char *topic, const void *data, size_t len)
{
    Greenhouse* greenhouse = (Greenhouse*)context;

    const char *payload = (const char *)data;
    float currentOutsideTemperature = String(payload).toFloat();

    greenhouse->m_Signals.tempOutside = currentOutsideTemperature;
}

void Greenhouse::Greenhouse::onCurrentPropabilityOfRainHandler(void *context, const char *topic, const void *data, size_t len)
{
    Greenhouse* greenhouse = (Greenhouse*)context;
    
    const char *payload = (const char *)data;
    float currentPropabilityOfRain = String(payload).toFloat();

    greenhouse->m_Signals.IsRaining = currentPropabilityOfRain > 0.5f;
}

bool Greenhouse::Greenhouse::configure()
{
    Communication::mqttClient.subscribe("SmartPlant/WeatherData/currentTemperature", onCurrentPropabilityOfRainHandler, this);
    Communication::mqttClient.subscribe("SmartPlant/WeatherData/currentPropabilityOfRain", onCurrentPropabilityOfRainHandler, this);
    
    return true;
}