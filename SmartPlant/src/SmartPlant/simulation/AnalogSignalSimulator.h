#pragma once

#include <StopWatch.h>
#include "../library/AnalogSensor.h"

class AnalogSignalSimulator {
public:
  AnalogSignalSimulator(AnalogSensor& sensor, unsigned long refreshTime = 50, unsigned int dinamic = 100);
  bool execute();

private:
  AnalogSensor m_Sensor;
  unsigned int& m_Value;

  ZbW::StopWatch m_RefreshTimer; // ms
  unsigned int m_Dinamic; // 1% - 100%
};
