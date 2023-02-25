#include "WindowCtrl.h"

enum WindowState
{
    UNDEFINED, OPEN, CLOSED, OPENING, CLOSING
};


WindowCtrl::WindowCtrl(WindowSignals& signals)
    : m_Signals(signals)
{
    bool (*undefinedHandlerHandler)(FSM *fsm, tFSM_Reason reason, void *context) = [](FSM *fsm, tFSM_Reason reason, void *context)
        {
            WindowCtrl* windowCtrl = (WindowCtrl*)context;
            WindowSignals signals = windowCtrl->m_Signals;

            signals.do_OpenWindow = false;
            signals.do_CloseWindow = false;

            if (reason == tFSM_Reason::FSM_REASON_ENTER)
            {
                if (signals.di_WindowOpen)
                    fsm->NextStateSet(WindowState::OPEN);
                else if (signals.di_WindowClosed)
                    fsm->NextStateSet(WindowState::CLOSED);
                else if (windowCtrl->m_OpeningRequested)
                    fsm->NextStateSet(WindowState::OPENING);
                else 
                    fsm->NextStateSet(WindowState::CLOSING);
            }
            return true;
        };
    bool (*openHanlder)(FSM *fsm, tFSM_Reason reason, void *context) = [](FSM* fsm, tFSM_Reason reason, void *context)
        {
            WindowCtrl* windowCtrl = (WindowCtrl*)context;

            if (reason == tFSM_Reason::FSM_REASON_DO)
            {
                if (windowCtrl->m_ClosingRequested)
                    fsm->NextStateSet(WindowState::CLOSING);
            }
            return true;
        };
    bool (*closedHandler)(FSM *fsm, tFSM_Reason reason, void *context) = [](FSM* fsm, tFSM_Reason reason, void *context)
        {
            WindowCtrl* windowCtrl = (WindowCtrl*)context;

            if (reason == tFSM_Reason::FSM_REASON_DO)
            {
                if (windowCtrl->m_OpeningRequested)
                    fsm->NextStateSet(WindowState::OPENING);
            }
            return true;
        };
    bool (*openingHanlder)(FSM *fsm, tFSM_Reason reason, void *context) = [](FSM* fsm, tFSM_Reason reason, void *context)
        {
            WindowCtrl* windowCtrl = (WindowCtrl*)context;
            WindowSignals signals = windowCtrl->m_Signals;

            if (reason == tFSM_Reason::FSM_REASON_ENTER)
            {
                signals.do_OpenWindow = true;
                windowCtrl->m_OpeningRequested = false;
            }
            else if (reason == tFSM_Reason::FSM_REASON_DO)
            {
                if (signals.di_WindowOpen)
                    fsm->NextStateSet(WindowState::OPEN);

                if (windowCtrl->m_ClosingRequested)
                    fsm->NextStateSet(WindowState::CLOSING);

            }
            else if (reason == tFSM_Reason::FSM_REASON_EXIT)
            {
                signals.do_OpenWindow = false;
            }
            return true;
        };
    bool (*closingHandler)(FSM *fsm, tFSM_Reason reason, void *context) = [](FSM* fsm, tFSM_Reason reason, void *context)
            {
            WindowCtrl* windowCtrl = (WindowCtrl*)context;
            WindowSignals signals = windowCtrl->m_Signals;

            if (reason == tFSM_Reason::FSM_REASON_ENTER)
            {
                signals.do_CloseWindow = true;
                windowCtrl->m_ClosingRequested = false;
            }
            else if (reason == tFSM_Reason::FSM_REASON_DO)
            {
                if (signals.di_WindowClosed)
                    fsm->NextStateSet(WindowState::CLOSED);

                if (windowCtrl->m_OpeningRequested)
                    fsm->NextStateSet(WindowState::OPENING);

            }
            else if (reason == tFSM_Reason::FSM_REASON_EXIT)
            {
                signals.do_CloseWindow = false;
            }
            return true;
        };

    m_States = new tFSM_State[5]
    {
        tFSM_State{"Undefined", undefinedHandlerHandler},
        tFSM_State{"Open", openHanlder},
        tFSM_State{"Closed", closedHandler},
        tFSM_State{"Opening", openingHanlder},
        tFSM_State{"Closing", closingHandler}
    };

    m_Fsm = new FSM(WindowState::UNDEFINED, m_States, this);
}

WindowCtrl::~WindowCtrl()
{
    delete[] m_States;
    delete m_Fsm;
}

bool WindowCtrl::execute()
{
    m_Fsm->run();
    return true;
}

void WindowCtrl::open()
{
    if (m_Fsm->CurrentStateGet() == WindowState::OPENING)
        return;

    m_ClosingRequested = false;
    m_OpeningRequested = true;
}
void WindowCtrl::close()
{
    if (m_Fsm->CurrentStateGet() == WindowState::CLOSING)
        return;
    
    m_OpeningRequested = false;
    m_ClosingRequested = true;
}