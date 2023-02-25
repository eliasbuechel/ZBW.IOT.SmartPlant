#include "WindowSimulator.h"

WindowSimulator::WindowSimulator(bool& openSignal, bool& closedSignal, const bool& openingSignal, const bool& closingSignal)
    : s_Open(openSignal), s_Closed(closedSignal), s_Opening(openingSignal), s_Closing(closingSignal)
{}

bool WindowSimulator::execute()
{
    if (!s_Opening)
        m_OpeningStarted = false;
    
    if (!s_Closing)
        m_ClosingStarted = false;

    if (m_OpeningStarted && !s_Open && m_OpeningTimer.isTimeout())
    {
        s_Open = true;
        m_OpeningStarted = false;
    }

    if (m_ClosingStarted && !s_Closed && m_ClosingTimer.isTimeout())
    {
        s_Closed = true;
        m_ClosingStarted = false;
    }

    if (!m_OpeningStarted && s_Opening && !s_Open)
    {
        m_OpeningStarted = true;
        m_OpeningTimer.restart();
    }

    if (!m_ClosingStarted && s_Closing && !s_Closed)
    {
        m_ClosingStarted = true;
        m_ClosingTimer.restart();
    }

    return true;
}