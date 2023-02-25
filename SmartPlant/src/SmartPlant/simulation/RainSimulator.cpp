#include "RainSimulator.h"

BoolSimulator::BoolSimulator(bool& isRaingingSignal, unsigned long onDelayTime, unsigned long offDelayTime)
    : s_Signal(isRaingingSignal), m_onDelayTimer(ZbW::StopWatch(onDelayTime)), m_offDelayTimer(ZbW::StopWatch(offDelayTime))
{
    m_onDelayTimer.restart();
    m_offDelayTimer.restart();
}

bool BoolSimulator::execute()
{
    if (!s_Signal && m_onDelayTimer.isTimeout())
    {
        s_Signal = true;
        m_offDelayTimer.restart();
    }

    if (s_Signal && m_offDelayTimer.isTimeout())
    {
        s_Signal = false;
        m_onDelayTimer.restart();
    }

    return true;
}