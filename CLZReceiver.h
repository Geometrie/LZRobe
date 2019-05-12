#ifndef CLZRECEIVER_H
#define CLZRECEIVER_H
#include <sstream>
#include "CCanvas.h"
class CLZReceiver: public wxThread
{
public:
    CLZReceiver();
    virtual wxThread::ExitCode Entry();
    CCanvas *m_lpCanvas;
    wxInputStream *m_lpInputStream;
    bool m_bKeepLoop;
protected:
	enum SEPARATE_TYPE
	{
		ST_NO_SEPARATE,
		ST_SPACE,
		ST_ENTER,
	};
    enum DATA_TYPE
    {
        DT_NULL,
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
        DT_PV,
    };
	DATA_TYPE m_dtStatus;
	CGameBase::BoardPoint *m_lpbpAnalyzing;
	void m_fnRefresh();
	void m_fnResponse();
	void m_fnApplyCoordinate(char *lpstrMessage);
	void m_fnApplyDigit(char *lpstrMessage);
    DATA_TYPE m_fnClassifyCommand(char *lpstrCommand);
};
#endif // CLZRECEIVER_H
