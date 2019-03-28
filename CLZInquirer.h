#ifndef CLZINQUIRER_H
#define CLZINQUIRER_H
#include <wx/string.h>
#include <wx/stream.h>
#include "CGameBoardManager.h"
class CLZInquirer
{
public:
	wxOutputStream *m_lpOutputStream;
	int m_iThinkingTime, m_iAnalyzeInterval;
	bool m_bAcceptChange;
	CGameBoardManager m_GameBoardManager;
	CLZInquirer();
	void m_fnSetThinkingTime();
	void m_fnSendMoveInfo(CGameBase::ExtendMove *lpMove);
	void m_fnInquireMove();
	void m_fnInquireResult();
	void m_fnInquireAnalyze();
	void m_fnNotify();
};
#endif