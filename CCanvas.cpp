#include "CCanvas.h"
CCanvas::CCanvas(wxWindow *lpParent): CPainter(lpParent)
{
    m_bShowStep = false;
}


void CCanvas::m_fnShowResignResult()
{
    wxString wxstrResult;
    switch (m_GameBoardManager.m_scTurnColor)
    {
    case SC_BLACK:
        wxstrResult = wxString(STR_BLACK_RESIGN);
        break;
    case SC_WHITE:
        wxstrResult = wxString(STR_WHITE_RESIGN);
        break;
    default:
        wxstrResult = wxEmptyString;
        break;
    }
    wxMessageDialog MD(this, wxstrResult, _(STR_GAME_RESULT));
    MD.ShowModal();
}

void CCanvas::m_fnShowCountResult(char *lpstrMessage)
{
    wxMessageDialog MD(this, wxString(lpstrMessage, strlen(lpstrMessage)), _(STR_GAME_RESULT));
    MD.ShowModal();
}

void CCanvas::OnLeftButtonUp(wxMouseEvent &event)
{
    long xMouse, yMouse;
    int x, y;
    if (m_bAcceptChange && m_GameStatusManager.m_fnUserAuthorized(m_GameBoardManager.m_scTurnColor))
    {
        event.GetPosition(&xMouse, &yMouse);
        x = (xMouse - m_iLeft + m_iGridSize / 2) / m_iGridSize;
        y = (yMouse - m_iTop + m_iGridSize / 2) / m_iGridSize;
        if (x >= 0 && x <= 19 && y >= 0 && y <= 19)
        {
			m_fnChangePosition(x, y);
        }
    }
}

void CCanvas::OnRightButtonUp(wxMouseEvent &event)
{
	if (m_GameStatusManager.m_fnBothAuthorized())
	{
		m_fnBackward();
	}
}


void CCanvas::OnKeyUp(wxKeyEvent &event)
{
    int iKey;
    iKey = event.GetKeyCode();
    switch (iKey)
    {
    case 'p':
    case 'P':
        if (m_GameStatusManager.m_fnUserAuthorized(m_GameBoardManager.m_scTurnColor))
        {
			m_fnChangePosition(-1, -1);
        }
    }
}



void CCanvas::OnPaint(wxPaintEvent&event)
{
	wxPoint ptMouse, ptClient;
    wxPaintDC pdc(this);
    wxBufferedDC dc(&pdc);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
	m_fnDrawGameBoard(dc);
	m_fnDrawPass(dc);
	m_fnDrawMoveTurn(dc);
	m_fnDrawStones(dc);
	m_fnDrawRecentMove(dc);
	ptMouse = wxGetMousePosition();
	ptClient = GetScreenPosition();
	if (m_GameStatusManager.m_fnAnalyzing())
	{
		m_fnDrawAnalyze(dc, (ptMouse.x - ptClient.x - m_iLeft + m_iGridSize / 2) / m_iGridSize, (ptMouse.y - ptClient.y - m_iTop + m_iGridSize / 2) / m_iGridSize);
	}
}


BEGIN_EVENT_TABLE(CCanvas, wxScrolledWindow)
EVT_LEFT_UP(CCanvas::OnLeftButtonUp)
EVT_RIGHT_UP(CCanvas::OnRightButtonUp)
EVT_KEY_UP(CCanvas::OnKeyUp)
EVT_SIZE(CCanvas::OnSize)
EVT_PAINT(CCanvas::OnPaint)
END_EVENT_TABLE()
