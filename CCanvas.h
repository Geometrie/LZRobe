#ifndef CCANVAS_H
#define CCANVAS_H
#include <fstream>
#include <math.h>
#include <wx/font.h>
#include <wx/toolbar.h>
#include <wx/scrolwin.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include <wx/menu.h>
#include "CLZProcess.h"
#include "CGameManager.h"
class CCanvas: public wxScrolledWindow
{
public:
    CCanvas(wxWindow *lpParent);
    CGameManager m_GameManager;
    wxOutputStream *m_lpOutputStream;
    wxPoint m_lpRecentMoveLogo[6];
    int m_iThinkingTime, m_iAnalyzeInterval;
    bool m_bShowStep, m_bWaiting;
    wxToolBar *m_lpToolBar;
    wxMenu *m_lpEditMenu;
    void m_fnAppendGameRecord();
    void m_fnToTheLastStep();
    void m_fnToTheFirstStep();
    void m_fnClearGameRecord();
    void m_fnBackward();
    void m_fnForward();
    void m_fnSetThinkingTime();
    void m_fnSendMoveInfo(CGameBase::ExtendMove *lpMove);
    void m_fnInquireMove();
    void m_fnInquireResult();
    void m_fnShowResignResult();
    void m_fnShowCountResult(char *lpstrMessage);
    void m_fnInquireAnalyze();
    void m_fnNotify();
    void m_fnRefreshPoint(CGameBase::BasePosition *bpPoint);
    void m_fnRefreshStep(CGameBase::ExtendMove *lpemStep);
    void m_fnEnableEngineRelatedTool();
    void m_fnDisableEngineRelatedTool();
private:
    int m_iWidth, m_iHeight, m_iGridSize, m_iLeft, m_iRight, m_iTop, m_iBottom, m_iRemainedSpace;
    wxFont m_fntPass, m_fntStep, m_fntAnalyze;
    wxColor m_clrLightRed, m_clrLightYellow, m_clrLightBlue, m_clrLightGreen;
    wxBrush m_brLightRed, m_brLightYellow, m_brLightBlue, m_brLightGreen;
    wxPen m_pnThickRed, m_pnThickGreen;
    void OnSize(wxSizeEvent &event);
    void OnPaint(wxPaintEvent &event);
    void OnLeftButtonUp(wxMouseEvent &event);
    void OnRightButtonUp(wxMouseEvent &event);
    void OnKeyUp(wxKeyEvent &event);
    DECLARE_EVENT_TABLE()
};


enum
{
    ID_SELECT_ENGINE = 1000,
    ID_SELECT_WEIGHT,
    ID_LEELA_ZERO,
    ID_BLACK_DOG,
    ID_WHITE_DOG,
    ID_ANALYZE,
    ID_SHOW_STEP,
    ID_FINAL_SCORE,
};
#endif // CCANVAS_H
