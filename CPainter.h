#ifndef CPAINTER_H
#define CPAINTER_H
#include <fstream>
#include <math.h>
#include <wx/font.h>
#include <wx/scrolwin.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include "CLZInquirer.h"

struct CCoverRange
{
	int iMinX, iMinY, iMaxX, iMaxY;
	CCoverRange()
	{
		iMinX = 18;
		iMinY = 18;
		iMaxX = 0;
		iMaxY = 0;
	}
	void m_fnRefresh(int x, int y)
	{
		if (x < iMinX)
		{
			iMinX = x;
		}
		if (y < iMinY)
		{
			iMinY = y;
		}
		if (x > iMaxX)
		{
			iMaxX = x;
		}
		if (y > iMaxY)
		{
			iMaxY = y;
		}
	}
};

class CPainter: public wxScrolledWindow, public CLZInquirer
{
public:
	CPainter(wxWindow *lpParent);
	CGameStatusManager m_GameStatusManager;
	bool m_bShowStep;
	int m_iWidth, m_iHeight, m_iGridSize, m_iLeft, m_iRight, m_iTop, m_iBottom, m_iRemainedSpace;
	wxFont m_fntPass, m_fntStep, m_fntAnalyze;
	wxColor m_clrLightRed, m_clrLightYellow, m_clrLightBlue, m_clrLightGreen;
	wxBrush m_brLightRed, m_brLightYellow, m_brLightBlue, m_brLightGreen;
	wxPen m_pnThickRed, m_pnThickGreen;
	wxPoint m_lpRecentMoveLogo[6];
	virtual void OnSize(wxSizeEvent &event);
	void m_fnAppendGameRecord();
	void m_fnRefreshAnalyze();
	void m_fnBackward();
	void m_fnForward();
	void m_fnChangePosition(int x, int y);
	void m_fnRefreshBoardRange(int iMinX, int iMinY, int iMaxX, int iMaxY);
	void m_fnRefreshBoardRange(CCoverRange *lpRange);
	void m_fnRefreshStep(CGameBase::ExtendMove *lpemStep);
protected:
	void m_fnDrawPass(wxBufferedDC &dc);
	void m_fnDrawGameBoard(wxBufferedDC &dc);
	void m_fnDrawMoveTurn(wxBufferedDC &dc);
	void m_fnDrawStones(wxBufferedDC &dc);
	void m_fnDrawRecentMove(wxBufferedDC &dc);
	void m_fnDrawAnalyze(wxBufferedDC &dc, int x, int y);
};
#endif