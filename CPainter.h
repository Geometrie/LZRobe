#ifndef CPAINTER_H
#define CPAINTER_H
#include <fstream>
#include <math.h>
#include <wx/font.h>
#include <wx/scrolwin.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include <wx/spinctrl.h>
#include "CLZInquirer.h"
#ifndef min
#define min(a, b) (((a) < (b))?(a):(b))
#endif
#define X_GAMEBOARD 8
#define Y_GAMEBOARD 0
#define X_TURN_TIP 4
#define Y_TURN_TIP 1
#define X_TURN_BLACK 2
#define X_TURN_WHITE 6
#define Y_TURN_STONE 4
#define SZ_TURN_LOGO 1
#define X_PRISONER_TIP 4
#define Y_PRISONER_TIP 6
#define X_BLACK_WRAP_WHITE 2
#define X_WHITE_WRAP_BLACK 6
#define Y_WRAP 9
#define SZ_PRISONER 1
#define Y_PRISONER_NUM 11
#define X_PASS_TIP 30
#define X_RESIGN_TIP 34
#define Y_NO_MOVE_TIP 1
#define Y_TIP_ARROW 2
#define SZ_TIP_ARROW 1
#define Y_NO_MOVE_LOGO 3
#define X_PROCESS_TIP 32
#define Y_PROCESS_TIP 5
#define X_PROGRESS_GRAPH 28
#define Y_PROGRESS_GRAPH 6

enum COORDINATE_TYPE
{
	CT_NULL,
	CT_NET,
	CT_NUM,
	CT_SGF,
	CT_GTP
};

class CPainter: public wxScrolledWindow, public CLZInquirer
{
public:
	CPainter(wxWindow *lpParent);
	clock_t m_ctTimeTick;
	bool m_bShowStep;
	COORDINATE_TYPE m_ctBoardTick;
	int m_iGridSize, m_iBoardUnitSize;
	int m_iBoardLeft, m_iBoardRight, m_iBoardTop, m_iBoardBottom;
	int m_iBackgroundLeft, m_iBackgroundTop, m_iBackgroundSize;
	int m_iTurnTipX, m_iTurnTipY, m_iTurnBlackX, m_iTurnBlackY, m_iTurnWhiteX, m_iTurnWhiteY, m_iTurnRadius;
	int m_iPrisonerTipX, m_iPrisonerTipY, m_lpiWrappedStonesX[2], m_iWrappedStonesY, m_iPrisonerRadius, m_iPrisonerNumY;
	int m_iPassTipX, m_iResignTipX, m_iNoMoveTipY, m_iTipArrowTop, m_iTipArrowBottom, m_iNoMoveLogoY;
	int m_iProcessTipX, m_iProcessTipY, m_iProgressGraphX, m_iProgressGraphY;
	wxFont m_fntPass, m_fntStep, m_fntAnalyze, m_fntTip, m_fntBranch;
	wxColour m_clrLightRed, m_clrLightYellow, m_clrLightBlue, m_clrLightGreen, m_clrMagenta;
	wxBrush m_brLightRed, m_brLightYellow, m_brLightBlue, m_brLightGreen, m_brGameBoard;
	wxPen m_pnThickRed, m_pnThickGreen, m_pnBlackLinePen, m_pnWhiteLinePen;
	wxPoint m_lppntRecentMoveLogo[6], m_lppntCorrectLogo[3], m_lppntErrorLogo[4];
	wxBitmap m_bmpOriginalBlackStone, m_bmpOriginalWhiteStone, m_bmpScaledBlackStone, m_bmpScaledWhiteStone, m_bmpOriginalPass, m_bmpOriginalResign;
	wxString m_wxstrTurn, m_wxstrPass, m_wxstrPrisoners, m_wxstrPassTip, m_wxstrResignTip, m_wxstrProcessTip;
	void m_fnSetSize();
protected:
	void m_fnDrawGameBoard(wxDC &dc);
	void m_fnDrawCoordinates(wxDC &dc);
	void m_fnDrawPass(wxDC &dc);
	void m_fnDrawMoveTurn(wxDC &dc);
	void m_fnDrawPrisoners(wxDC &dc);
	void m_fnDrawNoMoveChoice(wxDC &dc);
	void m_fnDrawProcess(wxDC &dc);
	void m_fnDrawStones(wxDC &dc);
	void m_fnDrawTerritory(wxDC &dc);
	void m_fnDrawRecentMove(wxDC &dc);
	void m_fnDrawBranch(wxDC &dc);
	void m_fnDrawAnalyze(wxDC &dc, int x, int y);
};
#endif