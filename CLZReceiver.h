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
		DT_LCB,
        DT_ORDER,
        DT_PV
    };
    DATA_TYPE m_dtStatus;
    void m_fnApplyMessage(char *lpstrMessage);
    DATA_TYPE m_fnClassifyCommand(char *lpstrCommand);
};
#endif // CLZRECEIVER_H
