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
    case SC_WHITE:
        wxstrResult = wxString(STR_BLACK_RESIGN);
        break;
    case SC_BLACK:
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
	wxPoint ptMouse, ptScroll;
    int x, y, xPos, yPos, iNewStep;
    if (m_bAcceptChange && m_GameStatusManager.m_fnUserAuthorized(m_GameBoardManager.m_scTurnColor))
    {
        ptMouse = event.GetPosition();
		ptScroll = GetViewStart();
		xPos = ptMouse.x + ptScroll.x * m_iGridSize;
		yPos = ptMouse.y + ptScroll.y * m_iGridSize;
        x = (xPos - m_iBoardLeft + m_iGridSize / 2) / m_iGridSize;
        y = (yPos - m_iBoardTop + m_iGridSize / 2) / m_iGridSize;
        if (x >= 0 && x <= 19 && y >= 0 && y <= 19)
        {
			m_fnChangePosition(x, y);
        }
		else
		{
			x = (xPos - m_iPassTipX + m_iGridSize / 2) / m_iGridSize;
			y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
			if (x == 0 && y == 0)
			{
				m_fnChangePosition(19, 0);
			}
			else
			{
				x = (xPos - m_iResignTipX + m_iGridSize / 2) / m_iGridSize;
				y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
				if (x == 0 && y == 0)
				{
					if (m_fnChangePosition(19, 1))
					{
						if (m_GameStatusManager.m_lpToolBar->GetToolState(ID_BLACK_DOG))
						{
							m_GameStatusManager.m_lpToolBar->ToggleTool(ID_BLACK_DOG, false);
							m_GameStatusManager.m_fnSetBlackDog();
						}
						if (m_GameStatusManager.m_lpToolBar->GetToolState(ID_WHITE_DOG))
						{
							m_GameStatusManager.m_lpToolBar->ToggleTool(ID_WHITE_DOG, false);
							m_GameStatusManager.m_fnSetWhiteDog();
						}
						if (m_GameStatusManager.m_lpToolBar->GetToolState(ID_ANALYZE))
						{
							m_GameStatusManager.m_lpToolBar->ToggleTool(ID_ANALYZE, false);
							m_GameStatusManager.m_fnSetAnalyze();
						}
						m_fnShowResignResult();
					}
				}
				else if (m_GameStatusManager.m_fnBothAuthorized())
				{
					x = ((xPos - m_iProgressGraphX) * 2 + m_iGridSize / 2) / m_iGridSize - 1;
					y = ((yPos - m_iProgressGraphY) * 2 + m_iGridSize / 2) / m_iGridSize;
					if ((x > 0 && y >= 0 && y < 25) || (x == 0 && y == 0))
					{
						iNewStep = (x - 1) * 25 + 13 + (x % 2 * 2 - 1) * (y - 12);
						if ((m_GameStatusManager.m_esCurrentEngine == ES_CLOSED || m_GameStatusManager.m_esCurrentEngine == ES_OPENED))
						{
							m_fnJumpTo(iNewStep);
							Refresh();
							if (m_GameStatusManager.m_fnAnalyzing())
							{
								m_fnInquireAnalyze();
							}
						}
					}
				}
			}
		}
		Refresh();
    }
}

void CCanvas::OnRightButtonUp(wxMouseEvent &event)
{
	if (m_GameStatusManager.m_fnBothAuthorized() && (m_GameStatusManager.m_esCurrentEngine == ES_CLOSED || m_GameStatusManager.m_esCurrentEngine == ES_OPENED))
	{
		m_fnBackward();
		Refresh();
		if (m_GameStatusManager.m_fnAnalyzing())
		{
			m_fnInquireAnalyze();
		}
	}
}

void CCanvas::OnPaint(wxPaintEvent&event)
{
	wxPoint ptMouse, ptClient, ptScroll;
    wxPaintDC pdc(this);
    wxBufferedDC dc(&pdc);
	int xPos, yPos, x, y;
	DoPrepareDC(dc);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
	m_fnDrawGameBoard(dc);
	m_fnDrawPass(dc);
	m_fnDrawMoveTurn(dc);
	m_fnDrawPrisoners(dc);
	m_fnDrawNoMoveChoice(dc);
	m_fnDrawProcess(dc);
	m_fnDrawStones(dc);
	m_fnDrawRecentMove(dc);
	if (m_GameStatusManager.m_fnAnalyzing())
	{
		ptMouse = wxGetMousePosition();
		ptClient = GetScreenPosition();
		ptScroll = GetViewStart();
		xPos = ptMouse.x - ptClient.x + ptScroll.x * m_iGridSize;
		yPos = ptMouse.y - ptClient.y + ptScroll.y * m_iGridSize;
		x = (xPos - m_iBoardLeft + m_iGridSize / 2) / m_iGridSize;
		y = (yPos - m_iBoardTop + m_iGridSize / 2) / m_iGridSize;
		if (x >= 0 && x <= 19 && y >= 0 && y <= 19)
		{
			m_fnDrawAnalyze(dc, x, y);
		}
		else
		{
			x = (xPos - m_iPassTipX + m_iGridSize / 2) / m_iGridSize;
			y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
			if (x == 0 && y == 0)
			{
				m_fnDrawAnalyze(dc, 19, 0);
			}
			else
			{
				m_fnDrawAnalyze(dc, -1, -1);
			}
		}
	}
}


BEGIN_EVENT_TABLE(CCanvas, wxScrolledWindow)
EVT_LEFT_UP(CCanvas::OnLeftButtonUp)
EVT_RIGHT_UP(CCanvas::OnRightButtonUp)
EVT_SIZE(CCanvas::OnSize)
EVT_PAINT(CCanvas::OnPaint)
END_EVENT_TABLE()
