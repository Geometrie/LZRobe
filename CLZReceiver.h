#ifndef CLZRECEIVER_H
#define CLZRECEIVER_H
#include <wx/thread.h>
#include "CCanvas.h"
class CLZReceiver: public wxThread
{
public:
    CLZReceiver();
    virtual wxThread::ExitCode Entry();
    CCanvas *m_lpCanvas;
    wxInputStream *m_lpInputStream;
    bool m_bKeepLoop, m_bRefresh;
    CGameBase::BoardPoint *m_lpbpAnalyzing;
    CGameBase::ExtendMove *m_lpemNew, *m_lpemLast;
    std::vector<CGameBase::BasePosition> m_vecbpAnalyzing;
protected:
    enum DATA_TYPE
    {
        DT_UNKNOWN,
        DT_RESULT,
        DT_EQUAL,
        DT_COORDINATE,
        DT_DIGIT,
        DT_MOVE,
        DT_INFO,
        DT_VISITS,
        DT_WINRATE,
        DT_PRIOR,
        DT_ORDER,
        DT_PV,
        DT_RESIGN
    };
    DATA_TYPE m_dtStatus;
    DATA_TYPE m_fnClassifyCommand(char *lpstrCommand);
    void m_fnApplyMessage(char *lpstrMessage);
};
#endif // CLZRECEIVER_H
