#include "CPainter.h"

CPainter::CPainter(wxWindow *lpParent): wxScrolledWindow(lpParent),
m_fntPass(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntStep(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntAnalyze(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_clrLightBlue(127, 127, 255),
m_clrLightGreen(127, 255, 127),
m_clrLightRed(255, 127, 127),
m_clrLightYellow(255, 255, 127),
m_pnThickRed(*wxRED, 3),
m_pnThickGreen(*wxGREEN, 3)
{
	m_brLightBlue = wxBrush(m_clrLightBlue);
	m_brLightGreen = wxBrush(m_clrLightGreen);
	m_brLightRed = wxBrush(m_clrLightRed);
	m_brLightYellow = wxBrush(m_clrLightYellow);
}


void CPainter::m_fnAppendGameRecord()
{
	int i;
	if (m_GameBoardManager.m_iStepPos > 0)
	{
		for (i = 0; i < m_GameBoardManager.m_iStepPos; ++i)
		{
			m_fnSendMoveInfo(&(m_GameBoardManager.m_vecRecords[i]));
		}
	}
}


void CPainter::m_fnRefreshAnalyze()
{
	m_GameBoardManager.m_bAcceptAnalyze = false;
	m_GameBoardManager.OnClearAnalyze();
	m_fnRefreshBoardRange(0, 0, 18, 18);
}

void CPainter::m_fnBackward()
{
	CGameBase::ExtendMove *lpemBack;
	char *lpstrCommand = (char*)"undo\n";
	if (m_GameBoardManager.OnBackMove())
	{
		m_fnRefreshAnalyze();
		lpemBack = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos]);
		m_fnRefreshStep(lpemBack);
		if (m_lpOutputStream != 0)
		{
			m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
		}
		if (m_GameStatusManager.m_fnAnalyzing())
		{
			m_fnInquireAnalyze();
		}
	}
}

void CPainter::m_fnForward()
{
	CGameBase::ExtendMove *lpemNew;
	if (m_GameBoardManager.OnRedoMove())
	{
		m_fnRefreshAnalyze();
		lpemNew = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos - 1]);
		m_fnRefreshStep(lpemNew);
		m_fnSendMoveInfo(lpemNew);
		if (m_GameStatusManager.m_fnAnalyzing())
		{
			m_fnInquireAnalyze();
		}
	}
}


void CPainter::m_fnChangePosition(int x, int y)
{
	CGameBase::ExtendMove *lpemNew;
	if (m_GameBoardManager.m_iStepPos == int(m_GameBoardManager.m_vecRecords.size()))
	{
		if (m_GameBoardManager.OnAddMove(x, y))
		{
			m_fnRefreshAnalyze();
			lpemNew = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos - 1]);
			m_fnRefreshStep(lpemNew);
			m_fnSendMoveInfo(&(*(m_GameBoardManager.m_vecRecords.rbegin())));
			if (m_GameBoardManager.m_iStepPos > 1)
			{
				lpemNew = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos - 2]);
				m_fnRefreshStep(lpemNew);
			}
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
			else
			{
				m_fnInquireResult();
			}
		}
	}
	else if (m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos].x == x && m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos].y == y)
	{
		m_fnForward();
	}
	else
	{
		if (m_GameBoardManager.OnTestMove(x, y))
		{
			wxMessageDialog MD(this, _("Are you sure to discard the previous variation?"), _("Warning"), wxOK | wxCANCEL);
			if (MD.ShowModal() == wxID_OK)
			{
				m_GameBoardManager.OnModifyGameRecord();
				if (m_GameBoardManager.OnAddMove(x, y))
				{
					m_fnRefreshAnalyze(); //m_GameBoardManager.OnClearAnalyze();
					lpemNew = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos - 1]);
					m_fnRefreshStep(lpemNew);
					m_fnSendMoveInfo(&(*(m_GameBoardManager.m_vecRecords.rbegin())));
					if (m_GameStatusManager.m_fnAnalyzing())
					{
						m_fnInquireAnalyze();
					}
				}
			}
		}
	}
}

void CPainter::m_fnRefreshBoardRange(int iMinX, int iMinY, int iMaxX, int iMaxY)
{
	RefreshRect(wxRect(m_iLeft + iMinX * m_iGridSize - m_iGridSize / 2, m_iTop + iMinY * m_iGridSize - m_iGridSize / 2 - 1, m_iGridSize * (iMaxX - iMinX + 1) + 2, m_iGridSize * (iMaxY - iMinY + 1) + 2));
}

void CPainter::m_fnRefreshBoardRange(CCoverRange *lpRange)
{
	m_fnRefreshBoardRange(lpRange->iMinX, lpRange->iMinY, lpRange->iMaxX, lpRange->iMaxY);
}

void CPainter::m_fnRefreshStep(CGameBase::ExtendMove *lpemStep)
{
	std::vector<CGameBase::BasePosition>::iterator iterRemove;
	CCoverRange rngStone;
	if (lpemStep->x >= 0 && lpemStep->x < 19 && lpemStep->y >= 0 && lpemStep->y < 19)
	{
		rngStone.m_fnRefresh(lpemStep->x, lpemStep->y);
		//RefreshRect(wxRect(m_iLeft + lpemStep->x * m_iGridSize - m_iGridSize / 2, m_iTop + lpemStep->y * m_iGridSize - m_iGridSize / 2, m_iGridSize, m_iGridSize));
		if (lpemStep->vecRemoved.size() > 0)
		{
			for (iterRemove = lpemStep->vecRemoved.begin(); iterRemove != lpemStep->vecRemoved.end(); ++iterRemove)
			{
				rngStone.m_fnRefresh(iterRemove->x, iterRemove->y);//m_fnRefreshPoint(&(*iterRemove));
			}
		}
		m_fnRefreshBoardRange(&rngStone);
	}
	else
	{
		RefreshRect(wxRect(m_iLeft + m_iGridSize / 2, m_iTop + m_iGridSize * 6 + m_iGridSize / 2, m_iGridSize * 17, m_iGridSize * 7));
	}
	RefreshRect(wxRect(m_iRemainedSpace / 8 - 1, m_iRemainedSpace / 8 - 1, m_iRemainedSpace / 4 + 2, m_iRemainedSpace / 4 + 2));
	RefreshRect(wxRect(m_iWidth - 3 * m_iRemainedSpace / 8 - 1, m_iRemainedSpace / 8 - 1, m_iRemainedSpace / 4 + 2, m_iRemainedSpace / 4 + 2));
}

void CPainter::OnSize(wxSizeEvent &event)
{
	int i;
	double dblAngle;
	GetSize(&m_iWidth, &m_iHeight);
	m_iRemainedSpace = m_iWidth - m_iHeight;
	m_iGridSize = m_iHeight / 20;
	m_iLeft = (m_iWidth) / 2 - m_iGridSize * 9;
	m_iRight = (m_iWidth) / 2 + m_iGridSize * 9;
	m_iTop = m_iHeight / 2 - m_iGridSize * 9;
	m_iBottom = m_iHeight / 2 + m_iGridSize * 9;
	for (i = 0; i < 3; ++i)
	{
		dblAngle = (i - 1) * M_PI * 2 / 3;
		m_lpRecentMoveLogo[i] = wxPoint(int(m_iGridSize * sin(dblAngle) / 2 + 0.5), int(m_iGridSize * cos(dblAngle) / 2 + 0.5));
		m_lpRecentMoveLogo[i + 3] = wxPoint(-m_lpRecentMoveLogo[i].x, -m_lpRecentMoveLogo[i].y);
	}
	m_fntPass.SetPixelSize(wxSize(m_iGridSize * 4, m_iGridSize * 8));
	m_fntAnalyze.SetPixelSize(wxSize(m_iGridSize / 6, m_iGridSize / 2));
	m_fntStep.SetPixelSize(wxSize(m_iGridSize / 4, m_iGridSize * 2 / 3));
	Refresh();
}

void CPainter::m_fnDrawPass(wxBufferedDC &dc)
{
	CGameBase::ExtendMove *lpemRecentMove;
	if (m_GameBoardManager.m_iStepPos > 0)
	{
		lpemRecentMove = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos - 1]);
		if (lpemRecentMove->x == -1 && lpemRecentMove->y == -1)
		{
			dc.SetFont(m_fntPass);
			dc.SetTextBackground(*wxWHITE);
			dc.SetTextForeground(*wxLIGHT_GREY);
			dc.DrawText(_("pass"), m_iLeft + m_iGridSize / 2, m_iTop + m_iGridSize * 13 / 4);
		}
	}
}


void CPainter::m_fnDrawGameBoard(wxBufferedDC &dc)
{
	int i;
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(*wxBLACK_BRUSH);
	for (i = 0; i < 19; ++i)
	{
		dc.DrawLine(m_iLeft + i * m_iGridSize, m_iTop, m_iLeft + i * m_iGridSize, m_iBottom);
	}
	for (i = 0; i < 19; ++i)
	{
		dc.DrawLine(m_iLeft, m_iTop + i * m_iGridSize, m_iRight, m_iTop + i * m_iGridSize);
	}
	for (i = 0; i < 9; ++i)
	{
		dc.DrawCircle(m_iLeft + m_iGridSize * ((i % 3) * 6 + 3), m_iTop + m_iGridSize * ((i / 3) * 6 + 3), m_iGridSize / 6);
	}
}


void CPainter::m_fnDrawMoveTurn(wxBufferedDC &dc)
{
	int i;
	dc.DrawCircle(m_iRemainedSpace / 4, m_iRemainedSpace / 4, m_iRemainedSpace / 8);
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawCircle(m_iWidth - m_iRemainedSpace / 4, m_iRemainedSpace / 4, m_iRemainedSpace / 8);
	switch (m_GameBoardManager.m_scTurnColor)
	{
	case SC_BLACK:
		dc.SetPen(m_pnThickRed);
		i = m_iRemainedSpace * 5 / 56;
		dc.DrawLine(m_iWidth - m_iRemainedSpace / 4 - i, m_iRemainedSpace / 4 - i, m_iWidth - m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 + i);
		dc.DrawLine(m_iWidth - m_iRemainedSpace / 4 - i, m_iRemainedSpace / 4 + i, m_iWidth - m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 - i);
		dc.SetPen(m_pnThickGreen);
		i = m_iRemainedSpace * 7 / 64;
		dc.DrawLine(m_iRemainedSpace / 4 - i, m_iRemainedSpace / 4 + m_iRemainedSpace / 16, m_iRemainedSpace / 4, m_iRemainedSpace / 4 + m_iRemainedSpace / 8);
		dc.DrawLine(m_iRemainedSpace / 4, m_iRemainedSpace / 4 + m_iRemainedSpace / 8, m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 - m_iRemainedSpace / 16);
		break;
	case SC_WHITE:
		dc.SetPen(m_pnThickRed);
		i = m_iRemainedSpace * 5 / 56;
		dc.DrawLine(m_iRemainedSpace / 4 - i, m_iRemainedSpace / 4 - i, m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 + i);
		dc.DrawLine(m_iRemainedSpace / 4 - i, m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 - i);
		dc.SetPen(m_pnThickGreen);
		i = m_iRemainedSpace * 7 / 64;
		dc.DrawLine(m_iWidth - m_iRemainedSpace / 4 - i, m_iRemainedSpace / 4 + m_iRemainedSpace / 16, m_iWidth - m_iRemainedSpace / 4, m_iRemainedSpace / 4 + m_iRemainedSpace / 8);
		dc.DrawLine(m_iWidth - m_iRemainedSpace / 4, m_iRemainedSpace / 4 + m_iRemainedSpace / 8, m_iWidth - m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 - m_iRemainedSpace / 16);
		break;
	default:
		break;
	}
}


void CPainter::m_fnDrawStones(wxBufferedDC &dc)
{
	std::list<CGameBase::BoardPoint*>::iterator iterVisitor;
	int i;
	if (m_GameBoardManager.m_lstExistingStones.size() > 0)
	{
		for (iterVisitor = m_GameBoardManager.m_lstExistingStones.begin(); iterVisitor != m_GameBoardManager.m_lstExistingStones.end(); ++iterVisitor)
		{
			i = (*iterVisitor) - m_GameBoardManager.m_lpGameBoard;
			if ((*iterVisitor)->stone_color == SC_BLACK)
			{
				dc.SetPen(*wxBLACK_PEN);
				dc.SetBrush(*wxBLACK_BRUSH);
				dc.DrawCircle(m_iLeft + m_iGridSize * (i / 19), m_iTop + m_iGridSize * (i % 19), m_iGridSize / 2);
			}
			else if ((*iterVisitor)->stone_color == SC_WHITE)
			{
				dc.SetPen(*wxBLACK_PEN);
				dc.SetBrush(*wxWHITE_BRUSH);
				dc.DrawCircle(m_iLeft + m_iGridSize * (i / 19), m_iTop + m_iGridSize * (i % 19), m_iGridSize / 2);
			}
		}
	}
}


void CPainter::m_fnDrawRecentMove(wxBufferedDC &dc)
{
	CGameBase::ExtendMove *lpemRecentMove;
	if (m_GameBoardManager.m_iStepPos > 0)
	{
		lpemRecentMove = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos - 1]);
		if (lpemRecentMove->x >= 0 && lpemRecentMove->x <= 19 && lpemRecentMove->y >= 0 && lpemRecentMove->y < 19)
		{
			dc.SetBrush(*wxTRANSPARENT_BRUSH);
			if (m_bShowStep)
			{
				dc.SetFont(m_fntStep);
				if (lpemRecentMove->stone_color == SC_BLACK)
				{
					dc.SetTextBackground(*wxBLACK);
					dc.SetTextForeground(*wxWHITE);
				}
				else if (lpemRecentMove->stone_color == SC_WHITE)
				{
					dc.SetTextBackground(*wxWHITE);
					dc.SetTextForeground(*wxBLACK);
				}
				if (m_GameBoardManager.m_iStepPos >= 1 && m_GameBoardManager.m_iStepPos < 10)
				{
					dc.DrawText(wxString::Format(wxString("%d"), m_GameBoardManager.m_iStepPos), m_iLeft + lpemRecentMove->x * m_iGridSize - m_iGridSize / 6, m_iTop + lpemRecentMove->y * m_iGridSize - m_iGridSize / 3);
				}
				else if (m_GameBoardManager.m_iStepPos >= 10 && m_GameBoardManager.m_iStepPos < 100)
				{
					dc.DrawText(wxString::Format(wxString("%d"), m_GameBoardManager.m_iStepPos), m_iLeft + lpemRecentMove->x * m_iGridSize - m_iGridSize / 3, m_iTop + lpemRecentMove->y * m_iGridSize - m_iGridSize / 3);
				}
				else
				{
					dc.DrawText(wxString::Format(wxString("%d"), m_GameBoardManager.m_iStepPos), m_iLeft + lpemRecentMove->x * m_iGridSize - m_iGridSize / 2, m_iTop + lpemRecentMove->y * m_iGridSize - m_iGridSize / 3);
				}
			}
			else
			{
				if (lpemRecentMove->stone_color == SC_BLACK)
				{
					dc.SetPen(*wxWHITE_PEN);
				}
				else if (lpemRecentMove->stone_color == SC_WHITE)
				{
					dc.SetPen(*wxBLACK_PEN);
				}
				dc.DrawPolygon(3, m_lpRecentMoveLogo, m_iLeft + lpemRecentMove->x * m_iGridSize, m_iTop + lpemRecentMove->y * m_iGridSize);
				dc.DrawPolygon(3, m_lpRecentMoveLogo + 3, m_iLeft + lpemRecentMove->x * m_iGridSize, m_iTop + lpemRecentMove->y * m_iGridSize);
			}
		}
	}
}

void CPainter::m_fnDrawAnalyze(wxBufferedDC &dc, int x, int y)
{
	int iMaxVisit, i;
	CGameBase::BoardPoint *lpbpLearningPoint;
	StoneColor scTest;
	CGameBase::BasePosition *lpbpTest;//std::vector<CGameBase::BasePosition>::iterator iterTestVisitor;
	std::vector<CGameBase::BoardPoint*>::iterator iterBoardVisitor;
	CGameBase::BoardPoint *lpbpDraw;
	if (x >= 0 && x < 19 && y >= 0 && y < 19 && m_GameBoardManager.m_fnPoint(x, y)->visits > 0)
	{
		lpbpLearningPoint = m_GameBoardManager.m_fnPoint(x, y);
		if (lpbpLearningPoint->pv_len > 0)//(lpBoardPoint->pv.size() > 1)
		{
			dc.SetFont(m_fntStep);
			scTest = m_GameBoardManager.m_scTurnColor;
			lpbpTest = lpbpLearningPoint->pv;
			for (i = 0; i < lpbpLearningPoint->pv_len; ++i)//(iterTestVisitor = lpBoardPoint->pv.begin(); iterTestVisitor != lpBoardPoint->pv.end(); ++iterTestVisitor)
			{
				if (lpbpTest->x >= 0 && lpbpTest->x < 19 && lpbpTest->y >= 0 && lpbpTest->y < 19)//(iterTestVisitor->x >= 0 && iterTestVisitor->x < 19 && iterTestVisitor->y >= 0 && iterTestVisitor->y <= 19)
				{
					if (scTest == SC_BLACK)
					{
						dc.SetPen(*wxBLACK_PEN);
						dc.SetBrush(*wxBLACK_BRUSH);
						dc.DrawCircle(m_iLeft + m_iGridSize * (lpbpTest->x), m_iTop + m_iGridSize * (lpbpTest->y), m_iGridSize / 2);//dc.DrawCircle(m_iLeft + m_iGridSize * (iterTestVisitor->x), m_iTop + m_iGridSize * (iterTestVisitor->y), m_iGridSize / 2);
						dc.SetTextBackground(*wxBLACK);
						dc.SetTextForeground(*wxWHITE);
						dc.DrawText(wxString::Format(wxString("%c"), (i + 'a')), m_iLeft + lpbpTest->x * m_iGridSize - m_iGridSize / 6, m_iTop + lpbpTest->y * m_iGridSize - m_iGridSize / 3);
					}
					if (scTest == SC_WHITE)
					{
						dc.SetPen(*wxBLACK_PEN);
						dc.SetBrush(*wxWHITE_BRUSH);
						dc.DrawCircle(m_iLeft + m_iGridSize * (lpbpTest->x), m_iTop + m_iGridSize * (lpbpTest->y), m_iGridSize / 2);//dc.DrawCircle(m_iLeft + m_iGridSize * (iterTestVisitor->x), m_iTop + m_iGridSize * (iterTestVisitor->y), m_iGridSize / 2);
						dc.SetTextBackground(*wxWHITE);
						dc.SetTextForeground(*wxBLACK);
						dc.DrawText(wxString::Format(wxString("%c"), (i + 'a')), m_iLeft + lpbpTest->x * m_iGridSize - m_iGridSize / 6, m_iTop + lpbpTest->y * m_iGridSize - m_iGridSize / 3);
					}
				}
				++lpbpTest;
				scTest = CGoRuleKeeper::opposite_color(scTest);
			}
		}
	}
	else
	{
		iMaxVisit = 0;
		for (iterBoardVisitor = m_GameBoardManager.m_vecAnalyzingStones.begin(); iterBoardVisitor != m_GameBoardManager.m_vecAnalyzingStones.end(); ++iterBoardVisitor)
		{
			lpbpDraw = (*iterBoardVisitor);
			if (lpbpDraw->visits > iMaxVisit)
			{
				iMaxVisit = lpbpDraw->visits;
			}
		}
		if (iMaxVisit > 0)
		{
			dc.SetFont(m_fntAnalyze);
			for (iterBoardVisitor = m_GameBoardManager.m_vecAnalyzingStones.begin(); iterBoardVisitor != m_GameBoardManager.m_vecAnalyzingStones.end(); ++iterBoardVisitor)//for (i = 0; i < 361; ++i)
			{
				lpbpDraw = (*iterBoardVisitor);
				if (lpbpDraw->visits > 0)
				{
					i = int(lpbpDraw - m_GameBoardManager.m_lpGameBoard);
					x = i / 19;
					y = i % 19;
					dc.SetTextForeground(*wxBLACK);
					if (lpbpDraw->visits * 4 > iMaxVisit * 3)
					{
						dc.SetBrush(m_brLightGreen);
						dc.SetTextBackground(m_clrLightGreen);
					}
					else if (lpbpDraw->visits * 2 > iMaxVisit)
					{
						dc.SetBrush(m_brLightBlue);
						dc.SetTextBackground(m_clrLightBlue);
					}
					else if (lpbpDraw->visits * 4 > iMaxVisit)
					{
						dc.SetBrush(m_brLightYellow);
						dc.SetTextBackground(m_clrLightYellow);
					}
					else
					{
						dc.SetBrush(m_brLightRed);
						dc.SetTextBackground(m_clrLightRed);
					}
					dc.SetPen(*wxTRANSPARENT_PEN);
					dc.DrawCircle(m_iLeft + m_iGridSize * x, m_iTop + m_iGridSize * y, m_iGridSize / 2);
					dc.DrawText(wxString::Format(wxString("%d"), lpbpDraw->win_rate), m_iLeft + m_iGridSize * x - m_iGridSize * 3 / 8, m_iTop + m_iGridSize * y - m_iGridSize / 2);
					if (lpbpDraw->visits >= 1 && lpbpDraw->visits < 10)
					{
						dc.DrawText(wxString::Format(wxString("%d"), lpbpDraw->visits), m_iLeft + m_iGridSize * x - m_iGridSize / 8, m_iTop + m_iGridSize * y);
					}
					else if (lpbpDraw->visits >= 10 && lpbpDraw->visits < 100)
					{
						dc.DrawText(wxString::Format(wxString("%d"), lpbpDraw->visits), m_iLeft + m_iGridSize * x - m_iGridSize / 4, m_iTop + m_iGridSize * y);
					}
					else if (lpbpDraw->visits >= 100 && lpbpDraw->visits < 1000)
					{
						dc.DrawText(wxString::Format(wxString("%d"), lpbpDraw->visits), m_iLeft + m_iGridSize * x - m_iGridSize * 3 / 8, m_iTop + m_iGridSize * y);
					}
					else
					{
						dc.DrawText(wxString::Format(wxString("%d"), lpbpDraw->visits), m_iLeft + m_iGridSize * x - m_iGridSize / 2, m_iTop + m_iGridSize * y);
					}
				}
			}
		}
	}
}