#include "AnalogSignalSimulator.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

const unsigned int MAX_DINAMIC_IN_PERCENT = 100;
const unsigned int MIN_DINAMIC_IN_PERCENT = 0;
const unsigned int MAX_DELTA_IN_PERCENT = 5;

AnalogSignalSimulator::AnalogSignalSimulator(AnalogSensor& sensor, unsigned long refreshTime, unsigned int dinamic)
    : m_Sensor(sensor), m_Value((unsigned int&)sensor.getSingal()), m_RefreshTimer(ZbW::StopWatch(refreshTime)), m_Dinamic(dinamic)
{
    
    m_Value = (m_Sensor.getMinSignal() + m_Sensor.getMaxSignal()) / 2; // start at middle of range

    assert(m_Dinamic >= MIN_DINAMIC_IN_PERCENT && m_Dinamic <= MAX_DINAMIC_IN_PERCENT);

    srand(time(NULL)); // seed random number generator
}

bool AnalogSignalSimulator::execute()
{
    if (!m_RefreshTimer.isTimeout())
        return true;

    m_RefreshTimer.restart();

    const unsigned int lowerBound = m_Sensor.getMinSignal();
    const unsigned int upperBound = m_Sensor.getMaxSignal();
    float range = upperBound - lowerBound;
    const float maxDelta = range * MAX_DELTA_IN_PERCENT / 100.0f;
    float seedDelta = (float) rand() / RAND_MAX * 2 - 1; // random delta from -1 to +1

    // adjust delta sign to prevent bias towards upper bound
    if (seedDelta < 0 && m_Value < lowerBound + maxDelta) {
        seedDelta = -seedDelta;
    } else if (seedDelta > 0 && m_Value > upperBound - maxDelta) {
        seedDelta = -seedDelta;
    }

    int delta = (int)(seedDelta * maxDelta * m_Dinamic / 100.0f);

    // adjust bounds checking to prevent bias towards upper bound
    if (delta < 0 && m_Value + delta < lowerBound) {
        m_Value = lowerBound;
    } else if (delta > 0 && m_Value + delta > upperBound) {
        m_Value = upperBound;
    } else {
        m_Value += delta;
    }

    return true;
}