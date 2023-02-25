#pragma once

#include <StopWatch.h>

class WindowSimulator
{
public:
    WindowSimulator(bool& openSignal, bool& closedSignal, const bool& openingSignal, const bool& closingSignal);
    bool execute();

private:
    bool& s_Open;
    bool& s_Closed;
    const bool& s_Opening;
    const bool& s_Closing;

    bool m_OpeningStarted;
    bool m_ClosingStarted;

    ZbW::StopWatch m_OpeningTimer = ZbW::StopWatch(2000);
    ZbW::StopWatch m_ClosingTimer = ZbW::StopWatch(3000);
};