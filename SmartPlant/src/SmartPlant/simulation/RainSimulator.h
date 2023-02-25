#pragma once

#include <StopWatch.h>

class BoolSimulator
{
public:
    BoolSimulator(bool& isRaingingSignal, unsigned long onDelayTime, unsigned long offDelayTime);
    bool execute();

private:
    bool& s_Signal;
    ZbW::StopWatch m_onDelayTimer;
    ZbW::StopWatch m_offDelayTimer;
};