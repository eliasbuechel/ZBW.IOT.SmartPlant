# pragma once

#include <fsm.h>

struct WindowSignals
{
    const unsigned int& di_WindowOpen;
    const unsigned int& di_WindowClosed;
    bool& do_OpenWindow;
    bool& do_CloseWindow;
};

class WindowCtrl
{
public:
    WindowCtrl(WindowSignals& signals);
    ~WindowCtrl();
    bool execute();
    void open();
    void close();

private:
    WindowSignals& m_Signals;

    FSM* m_Fsm;
    tFSM_State* m_States;

    bool m_OpeningRequested = false;
    bool m_ClosingRequested = false;
};