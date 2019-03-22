#include "CCanvas.h"
#define min(a, b) ((a) < (b))?(a):(b)
CCanvas::CCanvas(wxWindow *lpWindow): wxScrolledWindow(lpWindow),
m_fntPass(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntStep(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntAnalyze(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_clrLightBlue(127, 127, 255),
m_clrLightGreen(127, 255, 127),
m_clrLightRed(255, 127, 127),
m_clrLightYellow(255, 255, 127),
m_brLightBlue(m_clrLightBlue),
m_brLightGreen(m_clrLightGreen),
m_brLightRed(m_clrLightRed),
m_brLightYellow(m_clrLightYellow),
m_pnThickRed(*wxRED, 3),
m_pnThickGreen(*wxGREEN, 3)
{
    m_lpOutputStream = 0;
    m_bShowStep = false;
    m_bWaiting = true;
}

void CCanvas::m_fnSetThinkingTime()
{
    wxString wxstrCommand = wxString("time_settings 0 ") + wxString::Format(wxString("%d"), m_iThinkingTime) + wxString(" 1\n");
    m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
}

void CCanvas::m_fnSendMoveInfo(CGameBase::ExtendMove *lpMove)
{
    char lpstrCommand[16] = {'\0'};
    if (m_lpOutputStream != 0)
    {
        strcpy(lpstrCommand, "play ");
        lpMove->export_move(lpstrCommand + 5);
        strcat(lpstrCommand, "\n");
        m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
    }
}

void CCanvas::m_fnInquireMove()
{
    char lpstrCommand[16] = {'\0'};
    if (m_lpOutputStream != 0)
    {
        strcpy(lpstrCommand, "genmove ");
        switch (m_GameManager.m_scTurnColor)
        {
        case CGameBase::SC_BLACK:
            strcat(lpstrCommand, " b\n");
            break;
        case CGameBase::SC_WHITE:
            strcat(lpstrCommand, " w\n");
            break;
        default:
            break;
        }
        m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
    }
}

void CCanvas::m_fnInquireResult()
{
    char lpstrCommand[] = "final_score\n";
    if (m_lpOutputStream != 0)
    {
        m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
    }
}

void CCanvas::m_fnShowResignResult()
{
    wxString wxstrResult;
    switch (m_GameManager.m_scTurnColor)
    {
    case CGameBase::SC_BLACK:
        wxstrResult = wxString("Black has resigned, white win!");
        break;
    case CGameBase::SC_WHITE:
        wxstrResult = wxString("White has resigned, black win!");
        break;
    default:
        wxstrResult = wxEmptyString;
        break;
    }
    wxMessageDialog MD(this, wxstrResult, _("Game Result"));
    MD.ShowModal();
}

void CCanvas::m_fnShowCountResult(char *lpstrMessage)
{
    wxMessageDialog MD(this, wxString(lpstrMessage, strlen(lpstrMessage)), _("Game Result"));
    MD.ShowModal();
}

void CCanvas::m_fnInquireAnalyze()
{
    wxString wxstrCommand;
    if (m_iAnalyzeInterval > 0 && m_lpOutputStream != 0)
    {
        wxstrCommand = wxString("lz-analyze ") + wxString::Format(wxString("%d"), m_iAnalyzeInterval) + wxString("\n");
        m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
    }
}

void CCanvas::m_fnNotify()
{
    if (m_lpOutputStream != 0)
    {
        m_lpOutputStream->Write("\n", 1);
    }
}

void CCanvas::m_fnRefreshPoint(CGameBase::BasePosition *bpPoint)
{
    RefreshRect(wxRect(m_iLeft + bpPoint->x * m_iGridSize - m_iGridSize / 2 - 1, m_iTop + bpPoint->y * m_iGridSize - m_iGridSize / 2 - 1, m_iGridSize + 2, m_iGridSize + 2));
}


void CCanvas::m_fnRefreshPoint(int x, int y)
{
	RefreshRect(wxRect(m_iLeft + x * m_iGridSize - m_iGridSize / 2 - 1, m_iTop + y * m_iGridSize - m_iGridSize / 2 - 1, m_iGridSize + 2, m_iGridSize + 2));
}

void CCanvas::m_fnRefreshStep(CGameBase::ExtendMove *lpemStep)
{
    std::vector<CGameBase::BasePosition>::iterator iterRemove;
    if (lpemStep->x >= 0 && lpemStep->x < 19 && lpemStep->y >= 0 && lpemStep->y < 19)
    {
        RefreshRect(wxRect(m_iLeft + lpemStep->x * m_iGridSize - m_iGridSize / 2, m_iTop + lpemStep->y * m_iGridSize - m_iGridSize / 2, m_iGridSize, m_iGridSize));
        if (lpemStep->vecRemoved.size() > 0)
        {
            for (iterRemove = lpemStep->vecRemoved.begin(); iterRemove != lpemStep->vecRemoved.end(); ++iterRemove)
            {
                m_fnRefreshPoint(&(*iterRemove));
            }
        }
    }
    else
    {
        RefreshRect(wxRect(m_iLeft + m_iGridSize / 2, m_iTop + m_iGridSize * 6 + m_iGridSize / 2, m_iGridSize * 17, m_iGridSize * 7));
    }
    RefreshRect(wxRect(m_iRemainedSpace / 8 - 1, m_iRemainedSpace / 8 - 1, m_iRemainedSpace / 4 + 2, m_iRemainedSpace / 4 + 2));
    RefreshRect(wxRect(m_iWidth - 3 * m_iRemainedSpace / 8 - 1, m_iRemainedSpace / 8 - 1, m_iRemainedSpace / 4 + 2, m_iRemainedSpace / 4 + 2));
}

void CCanvas::m_fnRefreshAnalyze()
{
	std::vector<int> vecIndChanged;
	std::vector<int>::iterator iterChange;
	m_GameManager.m_bAcceptAnalyze = false;
	m_GameManager.OnClearAnalyze(vecIndChanged);
	if (vecIndChanged.size() > 0)
	{
		for (iterChange = vecIndChanged.begin(); iterChange != vecIndChanged.end(); ++iterChange)
		{
			m_fnRefreshPoint((*iterChange) / 19, (*iterChange) % 19);
		}
		vecIndChanged.clear();
	}
}

void CCanvas::m_fnAppendGameRecord()
{
    int i;
    if (m_GameManager.m_iStepPos > 0)
    {
        for (i = 0; i < m_GameManager.m_iStepPos; ++i)
        {
            m_fnSendMoveInfo(&(m_GameManager.m_vecRecords[i]));
        }
    }
}

void CCanvas::m_fnToTheLastStep()
{
    while (m_GameManager.m_iStepPos < int(m_GameManager.m_vecRecords.size()))
    {
        m_fnForward();
    }
}

void CCanvas::m_fnBackward()
{
    CGameBase::ExtendMove *lpemBack;
    char *lpstrCommand = (char*)"undo\n";
    if (m_GameManager.OnBackMove())
    {
		m_fnRefreshAnalyze();//m_GameManager.OnClearAnalyze();
        lpemBack = &(m_GameManager.m_vecRecords[m_GameManager.m_iStepPos]);
        m_fnRefreshStep(lpemBack);
        if (m_lpOutputStream != 0)
        {
            m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
        }
        if (m_lpToolBar->GetToolState(ID_ANALYZE))
        {
            m_fnInquireAnalyze();
        }
    }
}

void CCanvas::m_fnForward()
{
    CGameBase::ExtendMove *lpemNew;
    if (m_GameManager.OnRedoMove())
    {
		m_fnRefreshAnalyze(); //m_GameManager.OnClearAnalyze();
        lpemNew = &(m_GameManager.m_vecRecords[m_GameManager.m_iStepPos - 1]);
        m_fnRefreshStep(lpemNew);
        m_fnSendMoveInfo(lpemNew);
        if (m_lpToolBar->GetToolState(ID_ANALYZE))
        {
            m_fnInquireAnalyze();
        }
    }
}

void CCanvas::m_fnEnableEngineRelatedTool()
{
    m_lpToolBar->EnableTool(wxID_SAVE, true);
    m_lpToolBar->EnableTool(ID_BLACK_DOG, true);
    m_lpToolBar->EnableTool(ID_WHITE_DOG, true);
    m_lpToolBar->EnableTool(ID_ANALYZE, true);
    m_lpToolBar->EnableTool(ID_FINAL_SCORE, true);
    m_bWaiting = false;
}

void CCanvas::m_fnDisableEngineRelatedTool()
{
    bool bBlackDog, bWhiteDog;
    bBlackDog = m_lpToolBar->GetToolState(ID_BLACK_DOG);
    bWhiteDog = m_lpToolBar->GetToolState(ID_WHITE_DOG);
    if (bBlackDog)
    {
        m_lpToolBar->ToggleTool(ID_BLACK_DOG, false);
    }
    if (bWhiteDog)
    {
        m_lpToolBar->ToggleTool(ID_WHITE_DOG, false);
    }
    if (bBlackDog || bWhiteDog)
    {
        m_lpEditMenu->Enable(wxID_UNDO, true);
        m_lpEditMenu->Enable(wxID_REDO, true);
        m_lpToolBar->EnableTool(wxID_UNDO, true);
        m_lpToolBar->EnableTool(wxID_REDO, true);
    }
    if (m_lpToolBar->GetToolState(ID_ANALYZE))
    {
        m_lpToolBar->ToggleTool(ID_ANALYZE, false);
    }
    m_lpToolBar->EnableTool(wxID_SAVE, false);
    m_lpToolBar->EnableTool(ID_BLACK_DOG, false);
    m_lpToolBar->EnableTool(ID_WHITE_DOG, false);
    m_lpToolBar->EnableTool(ID_ANALYZE, false);
    m_lpToolBar->EnableTool(ID_FINAL_SCORE, false);
    m_bWaiting = true;
}

void CCanvas::OnLeftButtonUp(wxMouseEvent &event)
{
    CGameBase::ExtendMove *lpemNew;
    long xMouse, yMouse;
    int x, y;
    bool bBlackDog, bWhiteDog;
    bBlackDog = m_lpToolBar->GetToolState(ID_BLACK_DOG);
    bWhiteDog = m_lpToolBar->GetToolState(ID_WHITE_DOG);
    if ((!bBlackDog && m_GameManager.m_scTurnColor == CGameBase::SC_BLACK) || (!bWhiteDog && m_GameManager.m_scTurnColor == CGameBase::SC_WHITE))
    {
        event.GetPosition(&xMouse, &yMouse);
        x = (xMouse - m_iLeft + m_iGridSize / 2) / m_iGridSize;
        y = (yMouse - m_iTop + m_iGridSize / 2) / m_iGridSize;
        if (x >= 0 && x <= 19 && y >= 0 && y <= 19)
        {
            if (m_GameManager.m_iStepPos == int(m_GameManager.m_vecRecords.size()))
            {
                if(m_GameManager.OnAddMove(x, y))
                {
					m_fnRefreshAnalyze(); //m_GameManager.OnClearAnalyze();
                    lpemNew = &(m_GameManager.m_vecRecords[m_GameManager.m_iStepPos - 1]);
                    m_fnRefreshStep(lpemNew);
                    if (m_GameManager.m_iStepPos > 1)
                    {
                        m_fnRefreshStep(&(m_GameManager.m_vecRecords[m_GameManager.m_iStepPos - 2]));
                    }
                    m_fnSendMoveInfo(&(*(m_GameManager.m_vecRecords.rbegin())));
                    if ((bBlackDog && m_GameManager.m_scTurnColor == CGameBase::SC_BLACK) || (bWhiteDog && m_GameManager.m_scTurnColor == CGameBase::SC_WHITE))
                    {
                        m_fnInquireMove();
                    }
                    else if (m_lpToolBar->GetToolState(ID_ANALYZE))
                    {
                        m_fnInquireAnalyze();
                    }
                }
            }
            else if (m_GameManager.m_vecRecords[m_GameManager.m_iStepPos].x == x && m_GameManager.m_vecRecords[m_GameManager.m_iStepPos].y == y)
            {
                m_fnForward();
            }
            else
            {
                if (m_GameManager.OnTestMove(x, y))
                {
                    wxMessageDialog MD(this, _("Are you sure to discard the previous variation?"), _("Warning"), wxOK | wxCANCEL);
                    if (MD.ShowModal() == wxID_OK)
                    {
                        m_GameManager.OnModifyGameRecord();
                        if (m_GameManager.OnAddMove(x, y))
                        {
							m_fnRefreshAnalyze(); //m_GameManager.OnClearAnalyze();
                            lpemNew = &(m_GameManager.m_vecRecords[m_GameManager.m_iStepPos - 1]);
                            m_fnRefreshStep(lpemNew);
                            m_fnSendMoveInfo(lpemNew);
                            if (m_lpToolBar->GetToolState(ID_ANALYZE))
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
    m_fnBackward();
}


void CCanvas::OnKeyUp(wxKeyEvent &event)
{
    int iKey;
    bool bBlackDog, bWhiteDog;
    CGameBase::ExtendMove *lpemNew;
    bBlackDog = m_lpToolBar->GetToolState(ID_BLACK_DOG);
    bWhiteDog = m_lpToolBar->GetToolState(ID_WHITE_DOG);
    iKey = event.GetKeyCode();
    switch (iKey)
    {
    case 'p':
    case 'P':
        if ((!bBlackDog && m_GameManager.m_scTurnColor == CGameBase::SC_BLACK) || (!bWhiteDog && m_GameManager.m_scTurnColor == CGameBase::SC_WHITE))
        {
            if (m_GameManager.m_iStepPos == int(m_GameManager.m_vecRecords.size()))
            {
                if(m_GameManager.OnAddMove(-1, -1))
                {
					m_fnRefreshAnalyze();//m_GameManager.OnClearAnalyze();
                    lpemNew = &(m_GameManager.m_vecRecords[m_GameManager.m_iStepPos - 1]);
                    m_fnRefreshStep(lpemNew);
                    m_fnSendMoveInfo(&(*(m_GameManager.m_vecRecords.rbegin())));
                    if (m_GameManager.m_bAlive)
                    {
                        if ((bBlackDog && m_GameManager.m_scTurnColor == CGameBase::SC_BLACK) || (bWhiteDog && m_GameManager.m_scTurnColor == CGameBase::SC_WHITE))
                        {
                            m_fnInquireMove();
                        }
                        else if (m_lpToolBar->GetToolState(ID_ANALYZE))
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
            else if (m_GameManager.m_vecRecords[m_GameManager.m_iStepPos].x == -1 && m_GameManager.m_vecRecords[m_GameManager.m_iStepPos].y == -1)
            {
                m_fnForward();
            }
            else
            {
                if (m_GameManager.OnTestMove(-1, -1))
                {
                    wxMessageDialog MD(this, _("Are you sure to discard the previous variation?"), _("Warning"), wxOK | wxCANCEL);
                    if (MD.ShowModal() == wxID_OK)
                    {
                        m_GameManager.OnModifyGameRecord();
                        if (m_GameManager.OnAddMove(-1, -1))
                        {
							m_fnRefreshAnalyze(); //m_GameManager.OnClearAnalyze();
                            lpemNew = &(m_GameManager.m_vecRecords[m_GameManager.m_iStepPos - 1]);
                            m_fnRefreshStep(lpemNew);
                            m_fnSendMoveInfo(&(*(m_GameManager.m_vecRecords.rbegin())));
                            if (m_lpToolBar->GetToolState(ID_ANALYZE))
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

void CCanvas::OnSize(wxSizeEvent &event)
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
        m_lpRecentMoveLogo[i] = wxPoint(int(m_iGridSize * sin(dblAngle) / 2 + 0.5), int (m_iGridSize * cos(dblAngle) / 2 + 0.5));
        m_lpRecentMoveLogo[i + 3] = wxPoint(-m_lpRecentMoveLogo[i].x, -m_lpRecentMoveLogo[i].y);
    }
    m_fntPass.SetPixelSize(wxSize(m_iGridSize * 4, m_iGridSize * 8));
    m_fntAnalyze.SetPixelSize(wxSize(m_iGridSize / 6, m_iGridSize / 2));
    m_fntStep.SetPixelSize(wxSize(m_iGridSize / 4, m_iGridSize * 2 / 3));
    Refresh();
}

void CCanvas::OnPaint(wxPaintEvent&event)
{
    wxPaintDC pdc(this);
    wxBufferedDC dc(&pdc);
    int i, iMaxVisit;
    CGameBase::ExtendMove *lpemRecentMove;
    CGameBase::BoardPoint *lpbpDraw;
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    dc.SetPen(*wxBLACK_PEN);
    if (m_GameManager.m_iStepPos > 0)
    {
        lpemRecentMove = &(m_GameManager.m_vecRecords[m_GameManager.m_iStepPos - 1]);
        dc.SetFont(m_fntPass);
        dc.SetTextBackground(*wxWHITE);
        dc.SetTextForeground(*wxLIGHT_GREY);
        if (lpemRecentMove->x == -1 && lpemRecentMove->y == -1)
        {
            dc.DrawText(_("pass"), m_iLeft + m_iGridSize / 2, m_iTop + m_iGridSize * 13 / 4);
        }
    }
    for (i = 0; i < 19; ++i)
    {
        dc.DrawLine(m_iLeft + i * m_iGridSize, m_iTop, m_iLeft + i * m_iGridSize, m_iBottom);
    }
    for (i = 0; i < 19; ++i)
    {
        dc.DrawLine(m_iLeft, m_iTop + i * m_iGridSize, m_iRight, m_iTop + i * m_iGridSize);
    }
    dc.SetBrush(*wxBLACK_BRUSH);
    for (i = 0; i < 9; ++i)
    {
        dc.DrawCircle(m_iLeft + m_iGridSize * ((i % 3) * 6 + 3), m_iTop + m_iGridSize * ((i / 3) * 6 + 3), m_iGridSize / 6);
    }
    dc.DrawCircle(m_iRemainedSpace / 4, m_iRemainedSpace / 4, m_iRemainedSpace / 8);
    dc.SetBrush(*wxWHITE_BRUSH);
    dc.DrawCircle(m_iWidth - m_iRemainedSpace / 4, m_iRemainedSpace / 4, m_iRemainedSpace / 8);
    switch (m_GameManager.m_scTurnColor)
    {
    case CGameBase::SC_BLACK:
        dc.SetPen(m_pnThickRed);
        i = m_iRemainedSpace * 5/ 56;
        dc.DrawLine(m_iWidth - m_iRemainedSpace / 4 - i, m_iRemainedSpace /4 - i, m_iWidth - m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 + i);
        dc.DrawLine(m_iWidth - m_iRemainedSpace / 4 - i, m_iRemainedSpace /4 + i, m_iWidth - m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 - i);
        dc.SetPen(m_pnThickGreen);
        i = m_iRemainedSpace * 7 / 64;
        dc.DrawLine(m_iRemainedSpace / 4 - i, m_iRemainedSpace /4 + m_iRemainedSpace / 16, m_iRemainedSpace / 4, m_iRemainedSpace / 4 + m_iRemainedSpace / 8);
        dc.DrawLine(m_iRemainedSpace / 4, m_iRemainedSpace /4 + m_iRemainedSpace / 8, m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 - m_iRemainedSpace / 16);
        break;
    case CGameBase::SC_WHITE:
        dc.SetPen(m_pnThickRed);
        i = m_iRemainedSpace * 5/ 56;
        dc.DrawLine(m_iRemainedSpace / 4 - i, m_iRemainedSpace /4 - i, m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 + i);
        dc.DrawLine(m_iRemainedSpace / 4 - i, m_iRemainedSpace /4 + i, m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 - i);
        dc.SetPen(m_pnThickGreen);
        i = m_iRemainedSpace * 7 / 64;
        dc.DrawLine(m_iWidth - m_iRemainedSpace / 4 - i, m_iRemainedSpace /4 + m_iRemainedSpace / 16, m_iWidth - m_iRemainedSpace / 4, m_iRemainedSpace / 4 + m_iRemainedSpace / 8);
        dc.DrawLine(m_iWidth - m_iRemainedSpace / 4, m_iRemainedSpace /4 + m_iRemainedSpace / 8, m_iWidth - m_iRemainedSpace / 4 + i, m_iRemainedSpace / 4 - m_iRemainedSpace / 16);
        break;
    default:
        break;
    }
    iMaxVisit = 0;
    lpbpDraw = m_GameManager.m_lpGameBoard;
    for (i = 0; i < 361; ++i)
    {
        if (lpbpDraw->stone_color == CGameBase::SC_NULL)
        {
            if(lpbpDraw->visits > iMaxVisit)
            {
                iMaxVisit = lpbpDraw->visits;
            }
        }
        ++lpbpDraw;
    }
    if (m_lpToolBar->GetToolState(ID_ANALYZE))
    {
        dc.SetFont(m_fntAnalyze);
    }
    dc.SetPen(*wxBLACK_PEN);
    lpbpDraw = m_GameManager.m_lpGameBoard;
    for (i = 0; i < 361; ++i)
    {
        if (lpbpDraw->stone_color == CGameBase::SC_BLACK)
        {
            dc.SetPen(*wxBLACK_PEN);
            dc.SetBrush(*wxBLACK_BRUSH);
            dc.DrawCircle(m_iLeft + m_iGridSize * (i / 19), m_iTop + m_iGridSize * (i % 19), m_iGridSize / 2);
        }
        else if (lpbpDraw->stone_color == CGameBase::SC_WHITE)
        {
            dc.SetPen(*wxBLACK_PEN);
            dc.SetBrush(*wxWHITE_BRUSH);
            dc.DrawCircle(m_iLeft + m_iGridSize * (i / 19), m_iTop + m_iGridSize * (i % 19), m_iGridSize / 2);
        }
        else if (m_lpToolBar->GetToolState(ID_ANALYZE) && lpbpDraw->visits > 0)
        {
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
            dc.DrawCircle(m_iLeft + m_iGridSize * (i / 19), m_iTop + m_iGridSize * (i % 19), m_iGridSize / 2);
            dc.DrawText(wxString::Format(wxString("%d"), lpbpDraw->win_rate), m_iLeft + m_iGridSize * (i / 19) - m_iGridSize * 3 / 8, m_iTop + m_iGridSize * (i % 19) - m_iGridSize / 2);
            if (lpbpDraw->visits >= 1 && lpbpDraw->visits < 10)
            {
                dc.DrawText(wxString::Format(wxString("%d"), lpbpDraw->visits), m_iLeft + m_iGridSize * (i / 19) - m_iGridSize / 8, m_iTop + m_iGridSize * (i % 19));
            }
            else if (lpbpDraw->visits >= 10 && lpbpDraw->visits < 100)
            {
                dc.DrawText(wxString::Format(wxString("%d"), lpbpDraw->visits), m_iLeft + m_iGridSize * (i / 19) - m_iGridSize / 4, m_iTop + m_iGridSize * (i % 19));
            }
            else if (lpbpDraw->visits >= 100 && lpbpDraw->visits < 1000)
            {
                dc.DrawText(wxString::Format(wxString("%d"), lpbpDraw->visits), m_iLeft + m_iGridSize * (i / 19) - m_iGridSize * 3 / 8, m_iTop + m_iGridSize * (i % 19));
            }
            else
            {
                dc.DrawText(wxString::Format(wxString("%d"), lpbpDraw->visits), m_iLeft + m_iGridSize * (i / 19) - m_iGridSize / 2, m_iTop + m_iGridSize * (i % 19));
            }
        }
        ++lpbpDraw;
    }
    if (m_GameManager.m_iStepPos > 0)
    {
        lpemRecentMove = &(m_GameManager.m_vecRecords[m_GameManager.m_iStepPos - 1]);
        if (lpemRecentMove->x >= 0 && lpemRecentMove->x <= 19 && lpemRecentMove->y >= 0 && lpemRecentMove->y < 19)
        {
            dc.SetBrush(*wxTRANSPARENT_BRUSH);
            if (m_bShowStep)
            {
                dc.SetFont(m_fntStep);
                if (lpemRecentMove->stone_color == CGameBase::SC_BLACK)
                {
                    dc.SetTextBackground(*wxBLACK);
                    dc.SetTextForeground(*wxWHITE);
                }
                else if (lpemRecentMove->stone_color == CGameBase::SC_WHITE)
                {
                    dc.SetTextBackground(*wxWHITE);
                    dc.SetTextForeground(*wxBLACK);
                }
                if (m_GameManager.m_iStepPos >= 1 && m_GameManager.m_iStepPos < 10)
                {
                    dc.DrawText(wxString::Format(wxString("%d"), m_GameManager.m_iStepPos), m_iLeft + lpemRecentMove->x * m_iGridSize - m_iGridSize / 6, m_iTop + lpemRecentMove->y * m_iGridSize - m_iGridSize / 3);
                }
                else if (m_GameManager.m_iStepPos >= 10 && m_GameManager.m_iStepPos < 100)
                {
                    dc.DrawText(wxString::Format(wxString("%d"), m_GameManager.m_iStepPos), m_iLeft + lpemRecentMove->x * m_iGridSize - m_iGridSize / 3, m_iTop + lpemRecentMove->y * m_iGridSize - m_iGridSize / 3);
                }
                else
                {
                    dc.DrawText(wxString::Format(wxString("%d"), m_GameManager.m_iStepPos), m_iLeft + lpemRecentMove->x * m_iGridSize - m_iGridSize / 2, m_iTop + lpemRecentMove->y * m_iGridSize - m_iGridSize / 3);
                }
            }
            else
            {
                if (lpemRecentMove->stone_color == CGameBase::SC_BLACK)
                {
                    dc.SetPen(*wxWHITE_PEN);
                }
                else if (lpemRecentMove->stone_color == CGameBase::SC_WHITE)
                {
                    dc.SetPen(*wxBLACK_PEN);
                }
                dc.DrawPolygon(3, m_lpRecentMoveLogo, m_iLeft + lpemRecentMove->x * m_iGridSize, m_iTop + lpemRecentMove->y * m_iGridSize);
                dc.DrawPolygon(3, m_lpRecentMoveLogo + 3, m_iLeft + lpemRecentMove->x * m_iGridSize, m_iTop + lpemRecentMove->y * m_iGridSize);
            }
        }
    }
}


BEGIN_EVENT_TABLE(CCanvas, wxScrolledWindow)
EVT_LEFT_UP(CCanvas::OnLeftButtonUp)
EVT_RIGHT_UP(CCanvas::OnRightButtonUp)
EVT_KEY_UP(CCanvas::OnKeyUp)
EVT_SIZE(CCanvas::OnSize)
EVT_PAINT(CCanvas::OnPaint)
END_EVENT_TABLE()
