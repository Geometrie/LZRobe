#include "CCanvas.h"
CCanvas::CCanvas(wxWindow *lpParent): CPainter(lpParent)
{
    m_bShowStep = false;
	SetBackgroundStyle(wxBG_STYLE_PAINT);
}


void CCanvas::m_fnShowResignResult()
{
    wxString wxstrResult;
    switch (m_GameBoardManager.m_scTurnColor)
    {
    case SC_WHITE:
        wxstrResult = wxString(STR_WHITE_RESIGN);
        break;
    case SC_BLACK:
        wxstrResult = wxString(STR_BLACK_RESIGN);
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


bool CCanvas::m_fnChangePosition(int x, int y)
{
	bool bChanged = false;
	StoneColor scLastMove;
	CGameBase::ExtendMove *lpemSearch;
	if (m_GameBoardManager.m_lpemCurrentMove->child == NULL)
	{
		scLastMove = m_GameBoardManager.m_scTurnColor;
		if (m_GameBoardManager.OnAddMove(x, y))
		{
			m_fnResetAnalyze();
			m_fnSendMoveInfo(m_GameBoardManager.m_lpemCurrentMove);
			if (m_GameBoardManager.m_bAlive)
			{
				if (m_GameStatusManager.m_fnInquireAI(m_GameBoardManager.m_scTurnColor))
				{
					m_fnInquireMove();
				}
				else if (m_GameStatusManager.m_fnAnalyzing())
				{
					m_fnInquireAnalyze();
				}
			}
			else if (x == nBoardSize && y == 0)
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
				m_fnInquireResult();
			}
			bChanged = true;
		}
	}
	else
	{
		lpemSearch = m_GameBoardManager.m_lpemCurrentMove->search(x, y);
		if (lpemSearch != NULL)
		{
			m_fnForward(lpemSearch);
			if (m_GameStatusManager.m_fnAnalyzing())
			{
				m_fnInquireAnalyze();
			}
			bChanged = true;
		}
		else
		{
			if (m_GameBoardManager.OnTestMove(x, y))
			{
				wxMessageDialog MD(this, _(STR_ADD_BRANCH_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
				if (MD.ShowModal() == wxID_OK)
				{
					if (!m_GameBoardManager.m_bAlive)
					{
						m_fnClearLZBoard();
						m_fnAppendGameRecord();
						m_GameBoardManager.m_bAlive = true;
					}
					if (m_GameBoardManager.OnAddMove(x, y))
					{
						m_fnResetAnalyze();
						m_fnSendMoveInfo(m_GameBoardManager.m_lpemCurrentMove);
						if (m_GameStatusManager.m_fnAnalyzing())
						{
							m_fnInquireAnalyze();
						}
						bChanged = true;
					}
				}
			}
		}
	}
	return bChanged;
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
        x = (xPos - m_iBoardLeft + m_iBoardUnitSize / 2) / m_iBoardUnitSize;
        y = (yPos - m_iBoardTop + m_iBoardUnitSize / 2) / m_iBoardUnitSize;
        if (x >= 0 && x < nBoardSize && y >= 0 && y < nBoardSize)
        {
			m_fnChangePosition(x, y);
			Refresh();
        }
		else
		{
			x = (xPos - m_iPassTipX + m_iGridSize / 2) / m_iGridSize;
			y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
			if (x == 0 && y == 0)
			{
				m_fnChangePosition(nBoardSize, 0);
				Refresh();
			}
			else
			{
				x = (xPos - m_iResignTipX + m_iGridSize / 2) / m_iGridSize;
				y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
				if (x == 0 && y == 0)
				{
					if (m_fnChangePosition(nBoardSize, 1))
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
    }
}

void CCanvas::OnRightButtonUp(wxMouseEvent &event)
{
	wxMessageDialog MD(this, _(STR_DELETE_BRANCH_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
	wxPoint ptMouse, ptScroll;
	int x, y, xPos, yPos;
	CGameBase::ExtendMove *lpemSearch;
	if (m_GameStatusManager.m_fnBothAuthorized() && (m_GameStatusManager.m_esCurrentEngine == ES_CLOSED || m_GameStatusManager.m_esCurrentEngine == ES_OPENED))
	{
		ptMouse = event.GetPosition();
		ptScroll = GetViewStart();
		xPos = ptMouse.x + ptScroll.x * m_iGridSize;
		yPos = ptMouse.y + ptScroll.y * m_iGridSize;
		x = (xPos - m_iBoardLeft + m_iBoardUnitSize / 2) / m_iBoardUnitSize;
		y = (yPos - m_iBoardTop + m_iBoardUnitSize / 2) / m_iBoardUnitSize;
		lpemSearch = NULL;
		if (x >= 0 && x <= nBoardSize && y >= 0 && y <= nBoardSize)
		{
			lpemSearch = m_GameBoardManager.m_lpemCurrentMove->search(x, y);
		}
		else
		{
			x = (xPos - m_iPassTipX + m_iGridSize / 2) / m_iGridSize;
			y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
			if (x == 0 && y == 0)
			{
				lpemSearch = m_GameBoardManager.m_lpemCurrentMove->search(nBoardSize, 0);
			}
		}
		if (lpemSearch == NULL)
		{
			m_fnBackward();
			Refresh();
			if (m_GameStatusManager.m_fnAnalyzing())
			{
				m_fnInquireAnalyze();
			}
		}
		else
		{
			if (MD.ShowModal() == wxID_OK)
			{
				m_GameBoardManager.OnDeleteBranch(lpemSearch);
				Refresh();
			}
		}
	}
}


void CCanvas::m_fnDrawBuffer(wxDC &dc)
{
	wxPoint ptMouse, ptClient, ptScroll;
	int xPos, yPos, x, y;
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	m_fnDrawGameBoard(dc);
	m_fnDrawCoordinates(dc);
	m_fnDrawPass(dc);
	m_fnDrawMoveTurn(dc);
	m_fnDrawPrisoners(dc);
	m_fnDrawNoMoveChoice(dc);
	m_fnDrawProcess(dc);
	m_fnDrawStones(dc);
	m_fnDrawRecentMove(dc);
	m_fnDrawBranch(dc);
	if (m_GameStatusManager.m_fnAnalyzing())
	{
		ptMouse = wxGetMousePosition();
		ptClient = GetScreenPosition();
		ptScroll = GetViewStart();
		xPos = ptMouse.x - ptClient.x + ptScroll.x * m_iGridSize;
		yPos = ptMouse.y - ptClient.y + ptScroll.y * m_iGridSize;
		x = (xPos - m_iBoardLeft + m_iBoardUnitSize / 2) / m_iBoardUnitSize;
		y = (yPos - m_iBoardTop + m_iBoardUnitSize / 2) / m_iBoardUnitSize;
		m_AnalyzeMutex.Lock();
		if (x >= 0 && x <= nBoardSize && y >= 0 && y <= nBoardSize)
		{
			m_fnDrawAnalyze(dc, x, y);
		}
		else
		{
			x = (xPos - m_iPassTipX + m_iGridSize / 2) / m_iGridSize;
			y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
			if (x == 0 && y == 0)
			{
				m_fnDrawAnalyze(dc, nBoardSize, 0);
			}
			else
			{
				m_fnDrawAnalyze(dc, -1, -1);
			}
		}
		m_AnalyzeMutex.Unlock();
	}
}

void CCanvas::OnSize(wxSizeEvent &event)
{
	m_fnSetSize();
}


void CCanvas::OnPaint(wxPaintEvent&event)
{
    wxAutoBufferedPaintDC dc(this);
	DoPrepareDC(dc);
	m_fnDrawBuffer(dc);
}


BEGIN_EVENT_TABLE(CCanvas, wxScrolledWindow)
EVT_LEFT_UP(CCanvas::OnLeftButtonUp)
EVT_RIGHT_UP(CCanvas::OnRightButtonUp)
EVT_SIZE(CCanvas::OnSize)
EVT_PAINT(CCanvas::OnPaint)
END_EVENT_TABLE()
