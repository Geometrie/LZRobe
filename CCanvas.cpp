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
	CGameBase::ExtendMove *lpemSearch;
	wxMessageDialog MD(this, _(STR_ADD_BRANCH_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
	bool bChanged = false;
	if (m_GameBoardManager.DoublePass(x, y))
	{
		if (m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
		{
			m_fnLZInquireResult();
			m_fnLZExecuteFirstInquire();
		}
	}
	else if (m_GameBoardManager.Resign(x, y))
	{
		m_fnShowResignResult();
	}
	else if(m_GameBoardManager.OnTestMove(x, y))
	{
		lpemSearch = m_GameBoardManager.m_lpemCurrentMove->search(x, y);
		if (m_GameBoardManager.m_lpemCurrentMove->child == NULL || lpemSearch != NULL || MD.ShowModal() == wxID_OK)
		{
			if (m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
			{
				if (m_GameStatusManager.m_fnAnalyzing())
				{
					m_GameBoardManager.OnClearAnalyze();
					m_fnLZAppendMove(m_GameBoardManager.m_scTurnColor, x, y);
					m_fnLZInquireAnalyze();
				}
				else
				{
					m_fnLZAppendMove(m_GameBoardManager.m_scTurnColor, x, y);
				}
				m_GameBoardManager.OnAddMove(x, y);
				Refresh();
				m_fnLZExecuteFirstInquire();
			}
			else
			{
				m_GameBoardManager.OnAddMove(x, y);
				Refresh();
			}
		}
		bChanged = true;
	}
	return bChanged;
}

void CCanvas::OnLeftButtonUp(wxMouseEvent &event)
{
	wxPoint ptMouse, ptScroll;
    int x, y, xPos, yPos, iNewStep;
    if (m_GameStatusManager.m_fnUserAuthorized(m_GameBoardManager.m_scTurnColor))
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
        }
		else
		{
			x = (xPos - m_iPassTipX + m_iGridSize / 2) / m_iGridSize;
			y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
			if (x == 0 && y == 0)
			{
				m_fnChangePosition(nBoardSize, 0);
			}
			else
			{
				x = (xPos - m_iResignTipX + m_iGridSize / 2) / m_iGridSize;
				y = (yPos - m_iNoMoveLogoY + m_iGridSize / 2) / m_iGridSize;
				if (x == 0 && y == 0)
				{
					m_fnChangePosition(nBoardSize, 1);
				}
				else if (m_GameStatusManager.m_fnBothAuthorized())
				{
					x = ((xPos - m_iProgressGraphX) * 2 + m_iGridSize / 2) / m_iGridSize - 1;
					y = ((yPos - m_iProgressGraphY) * 2 + m_iGridSize / 2) / m_iGridSize;
					if ((x > 0 && y >= 0 && y < 25) || (x == 0 && y == 0))
					{
						iNewStep = (x - 1) * 25 + 13 + (x % 2 * 2 - 1) * (y - 12);
						if (iNewStep >= 0 && iNewStep <= m_GameBoardManager.m_lpemCurrentMove->step + m_GameBoardManager.m_lpemCurrentMove->depth)
						{
							if (m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
							{
								if (m_GameStatusManager.m_fnAnalyzing())
								{
									m_GameBoardManager.OnClearAnalyze();
									m_fnLZJumpTo(iNewStep);
									m_fnLZInquireAnalyze();
								}
								else
								{
									m_fnLZJumpTo(iNewStep);
								}
								m_GameBoardManager.OnJumpTo(iNewStep);
								Refresh();
								m_fnLZExecuteFirstInquire();
							}
							else
							{
								m_GameBoardManager.OnJumpTo(iNewStep);
								Refresh();
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
		if (x >= 0 && x < nBoardSize && y >= 0 && y < nBoardSize || (x == nBoardSize && y == 0))
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
			if (m_GameBoardManager.m_lpemCurrentMove->parent != NULL)
			{
				if (m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
				{
					if (m_GameStatusManager.m_fnAnalyzing())
					{
						m_GameBoardManager.OnClearAnalyze();
						m_fnLZBackward();
						m_fnLZInquireAnalyze();
					}
					else
					{
						m_fnLZBackward();
					}
					m_GameBoardManager.OnBackMove();
					Refresh();
					m_fnLZExecuteFirstInquire();
				}
				else
				{
					m_GameBoardManager.OnBackMove();
					Refresh();
				}
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
