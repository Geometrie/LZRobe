#include "CPainter.h"

CPainter::CPainter(wxWindow *lpParent) : wxScrolledWindow(lpParent),
m_fntPass(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntStep(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntAnalyze(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntTip(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_clrLightBlue(127, 127, 255),
m_clrLightGreen(127, 255, 127),
m_clrLightRed(255, 127, 127),
m_clrLightYellow(255, 255, 127),
m_pnThickRed(*wxRED, 3),
m_pnThickGreen(*wxGREEN, 3),
m_pnBlackLinePen(*wxBLACK_PEN),
m_pnWhiteLinePen(*wxWHITE_PEN),
m_wxstrPass("Pass"),
m_wxstrTurn(STR_MOVE_TURN),
m_wxstrPrisoners(STR_PRISONERS),
m_wxstrPassTip(STR_PASS),
m_wxstrResignTip(STR_RESIGN),
m_wxstrProcessTip(STR_GAME_PROCESS)
{
	m_brLightBlue = wxBrush(m_clrLightBlue);
	m_brLightGreen = wxBrush(m_clrLightGreen);
	m_brLightRed = wxBrush(m_clrLightRed);
	m_brLightYellow = wxBrush(m_clrLightYellow);
	m_brGameBoard = wxBrush(wxColor(192, 220, 192));
	m_iGridSize = 25;
}

void CPainter::m_fnSetSize()
{

	int i;
	double dblAngle;
	wxImage imagScalor;
	m_iBoardLeft = X_GAMEBOARD * m_iGridSize;
	m_iBoardTop = Y_GAMEBOARD * m_iGridSize;
	m_iBoardRight = (X_GAMEBOARD + SZ_BOARD_SIZE) * m_iGridSize;
	m_iBoardBottom = (Y_GAMEBOARD + SZ_BOARD_SIZE) * m_iGridSize;
	m_iBackgroundLeft = m_iBoardLeft - m_iGridSize;
	m_iBackgroundTop = m_iBoardTop - m_iGridSize;
	m_iBackgroundSize = (SZ_BOARD_SIZE + 2) * m_iGridSize;
	m_iTurnTipX = X_TURN_TIP * m_iGridSize;
	m_iTurnTipY = Y_TURN_TIP * m_iGridSize;
	m_iTurnBlackX = X_TURN_BLACK * m_iGridSize;
	m_iTurnBlackY = Y_TURN_STONE * m_iGridSize - m_iGridSize / 2;
	m_iTurnWhiteX = X_TURN_WHITE * m_iGridSize;
	m_iTurnWhiteY = Y_TURN_STONE * m_iGridSize - m_iGridSize / 2;
	m_iTurnRadius = SZ_TURN_LOGO * m_iGridSize;
	m_iPrisonerTipX = X_PRISONER_TIP * m_iGridSize;
	m_iPrisonerTipY = Y_PRISONER_TIP * m_iGridSize;
	m_lpiWrappedStonesX[0] = X_BLACK_WRAP_WHITE * m_iGridSize;
	m_lpiWrappedStonesX[1] = X_WHITE_WRAP_BLACK * m_iGridSize;
	m_iWrappedStonesY = Y_WRAP * m_iGridSize;
	m_iPrisonerRadius = SZ_PRISONER * m_iGridSize / 2;
	m_iPrisonerNumY = Y_PRISONER_NUM * m_iGridSize;
	m_iPassTipX = X_PASS_TIP * m_iGridSize;
	m_iResignTipX = X_RESIGN_TIP * m_iGridSize;
	m_iNoMoveTipY = Y_NO_MOVE_TIP * m_iGridSize;
	m_iTipArrowTop = Y_TIP_ARROW * m_iGridSize;
	m_iTipArrowBottom = (Y_TIP_ARROW + SZ_TIP_ARROW) * m_iGridSize;
	m_iNoMoveLogoY = Y_NO_MOVE_LOGO * m_iGridSize;
	m_iProcessTipX = X_PROCESS_TIP * m_iGridSize;
	m_iProcessTipY = Y_PROCESS_TIP * m_iGridSize;
	m_iProgressGraphX = X_PROGRESS_GRAPH * m_iGridSize;
	m_iProgressGraphY = Y_PROGRESS_GRAPH * m_iGridSize + m_iGridSize / 2;
	m_lppntErrorLogo[0] = wxPoint(-(m_iGridSize * 5 + 3) / 7, (m_iGridSize * 5 + 3) / 7);
	m_lppntErrorLogo[1] = wxPoint((m_iGridSize * 5 + 3) / 7, -(m_iGridSize * 5 + 3) / 7);
	m_lppntErrorLogo[2] = wxPoint(-(m_iGridSize * 5 + 3) / 7, -(m_iGridSize * 5 + 3) / 7);
	m_lppntErrorLogo[3] = wxPoint((m_iGridSize * 5 + 3) / 7, (m_iGridSize * 5 + 3) / 7);
	m_lppntCorrectLogo[0] = wxPoint(-(m_iGridSize * 7 + 4) / 8, m_iGridSize / 2);
	m_lppntCorrectLogo[1] = wxPoint(0, m_iGridSize);
	m_lppntCorrectLogo[2] = wxPoint((m_iGridSize * 7 + 4) / 8, -m_iGridSize / 2);
	for (i = 0; i < 3; ++i)
	{
		dblAngle = (i - 1) * M_PI * 2 / 3;
		m_lppntRecentMoveLogo[i] = wxPoint(int(m_iGridSize * sin(dblAngle) / 2 + 0.5), int(m_iGridSize * cos(dblAngle) / 2 + 0.5));
		m_lppntRecentMoveLogo[i + 3] = wxPoint(-m_lppntRecentMoveLogo[i].x, -m_lppntRecentMoveLogo[i].y);
	}
	m_pnBlackLinePen.SetWidth(m_iGridSize / 16);
	m_pnWhiteLinePen.SetWidth(m_iGridSize / 16);
	m_fntPass.SetPixelSize(wxSize(m_iGridSize * 4, m_iGridSize * 8));
	m_fntAnalyze.SetPixelSize(wxSize(m_iGridSize / 6, m_iGridSize / 2));
	m_fntStep.SetPixelSize(wxSize(m_iGridSize * 1 / 4, m_iGridSize * 5 / 8));
	m_fntTip.SetPixelSize(wxSize(m_iGridSize * 2 / 5, m_iGridSize));
	imagScalor = m_bmpOriginalBlackStone.ConvertToImage();
	imagScalor.Rescale(m_iGridSize, m_iGridSize);
	imagScalor.SetMaskColour(255, 255, 255);
	m_bmpScaledBlackStone = wxBitmap(imagScalor);
	imagScalor.Clear();
	imagScalor = m_bmpOriginalWhiteStone.ConvertToImage();
	imagScalor.Rescale(m_iGridSize, m_iGridSize);
	imagScalor.SetMaskColour(255, 255, 255);
	m_bmpScaledWhiteStone = wxBitmap(imagScalor);
	imagScalor.Clear();
	SetScrollbars(m_iGridSize, m_iGridSize, 36, 20);
	Refresh();
}


bool CPainter::m_fnChangePosition(int x, int y)
{
	bool bChanged = false;
	if (m_GameBoardManager.m_iStepPos == int(m_GameBoardManager.m_vecRecords.size()))
	{
		if (m_GameBoardManager.OnAddMove(x, y))
		{
			m_fnRefreshAnalyze();
			m_fnSendMoveInfo(&(*(m_GameBoardManager.m_vecRecords.rbegin())));
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
			else if (x == 19 && y == 0)
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
	else if (m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos].x == x && m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos].y == y)
	{
		m_fnForward();
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
			wxMessageDialog MD(this, _(STR_CHANGE_RECORD_INQUIRY), _(STR_WARNING), wxOK | wxCANCEL);
			if (MD.ShowModal() == wxID_OK)
			{
				m_GameBoardManager.OnModifyGameRecord();
				if (!m_GameBoardManager.m_bAlive)
				{
					m_fnClearLZBoard();
					m_fnAppendGameRecord();
					m_GameBoardManager.m_bAlive = true;
				}
				if (m_GameBoardManager.OnAddMove(x, y))
				{
					m_fnRefreshAnalyze();
					m_fnSendMoveInfo(&(*(m_GameBoardManager.m_vecRecords.rbegin())));
					if (m_GameStatusManager.m_fnAnalyzing())
					{
						m_fnInquireAnalyze();
					}
					bChanged = true;
				}
			}
		}
	}
	return bChanged;
}


void CPainter::OnSize(wxSizeEvent &event)
{
	wxSize szClient;
	szClient = GetSize();
	m_iGridSize = szClient.GetHeight() / 20;
	m_fnSetSize();
}



void CPainter::m_fnDrawGameBoard(wxBufferedDC &dc)
{
	int i;
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.SetBrush(m_brGameBoard);
	dc.DrawRectangle(m_iBackgroundLeft, m_iBackgroundTop, m_iBackgroundSize, m_iBackgroundSize);
	dc.SetPen(m_pnBlackLinePen);
	for (i = 0; i <= SZ_BOARD_SIZE; ++i)
	{
		dc.DrawLine(m_iBoardLeft + m_iGridSize * i, m_iBoardTop,m_iBoardLeft + m_iGridSize * i, m_iBoardBottom);
	}
	for (i = 0; i < 19; ++i)
	{
		dc.DrawLine(m_iBoardLeft, m_iBoardTop + m_iGridSize * i, m_iBoardRight, m_iBoardTop + m_iGridSize * i);
	}
	dc.SetBrush(*wxBLACK_BRUSH);
	for (i = 0; i < 9; ++i)
	{
		dc.DrawCircle(m_iBoardLeft + m_iGridSize * ((i % 3) * 6 + 3), m_iBoardTop + m_iGridSize * ((i / 3) * 6 + 3), m_iGridSize / 6);
	}
}

void CPainter::m_fnDrawPass(wxBufferedDC &dc)
{
	CGameBase::ExtendMove *lpemRecentMove;
	wxSize szStringSize;
	if (m_GameBoardManager.m_iStepPos > 0)
	{
		lpemRecentMove = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos - 1]);
		if (lpemRecentMove->x == 19 && lpemRecentMove->y == 0)
		{
			dc.SetFont(m_fntPass);
			szStringSize = dc.GetTextExtent(m_wxstrPass);
			dc.SetTextBackground(*wxWHITE);
			dc.SetTextForeground(*wxLIGHT_GREY);
			dc.DrawText(m_wxstrPass, X_GAMEBOARD * m_iGridSize + (SZ_BOARD_SIZE  * m_iGridSize - szStringSize.x) / 2, Y_GAMEBOARD * m_iGridSize + SZ_BOARD_SIZE * m_iGridSize / 2 - szStringSize.y * 2 / 3);
		}
	}
}


void CPainter::m_fnDrawMoveTurn(wxBufferedDC &dc)
{
	wxSize szText;
	dc.SetTextForeground(*wxBLACK);
	dc.SetTextBackground(*wxWHITE);
	dc.SetFont(m_fntTip);
	szText = dc.GetTextExtent(m_wxstrTurn);
	dc.DrawText(m_wxstrTurn, m_iTurnTipX - szText.x / 2, m_iTurnTipY);
	dc.SetBrush(*wxBLACK_BRUSH);
	dc.DrawCircle(m_iTurnBlackX, m_iTurnBlackY, m_iTurnRadius);
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawCircle(m_iTurnWhiteX, m_iTurnWhiteY, m_iTurnRadius);
	switch (m_GameBoardManager.m_scTurnColor)
	{
	case SC_BLACK:
		dc.SetPen(m_pnThickRed);
		dc.DrawLine(m_iTurnWhiteX + m_lppntErrorLogo[0].x * SZ_TURN_LOGO, m_iTurnWhiteY + m_lppntErrorLogo[0].y * SZ_TURN_LOGO, m_iTurnWhiteX + m_lppntErrorLogo[1].x * SZ_TURN_LOGO, m_iTurnWhiteY + m_lppntErrorLogo[1].y * SZ_TURN_LOGO);
		dc.DrawLine(m_iTurnWhiteX + m_lppntErrorLogo[2].x * SZ_TURN_LOGO, m_iTurnWhiteY + m_lppntErrorLogo[2].y * SZ_TURN_LOGO, m_iTurnWhiteX + m_lppntErrorLogo[3].x * SZ_TURN_LOGO, m_iTurnWhiteY + m_lppntErrorLogo[3].y * SZ_TURN_LOGO);
		dc.SetPen(m_pnThickGreen);
		dc.DrawLine(m_iTurnBlackX + m_lppntCorrectLogo[0].x * SZ_TURN_LOGO, m_iTurnBlackY + m_lppntCorrectLogo[0].y * SZ_TURN_LOGO, m_iTurnBlackX + m_lppntCorrectLogo[1].x * SZ_TURN_LOGO, m_iTurnBlackY + m_lppntCorrectLogo[1].y * SZ_TURN_LOGO);
		dc.DrawLine(m_iTurnBlackX + m_lppntCorrectLogo[1].x * SZ_TURN_LOGO, m_iTurnBlackY + m_lppntCorrectLogo[1].y * SZ_TURN_LOGO, m_iTurnBlackX + m_lppntCorrectLogo[2].x * SZ_TURN_LOGO, m_iTurnBlackY + m_lppntCorrectLogo[2].y * SZ_TURN_LOGO);
		break;
	case SC_WHITE:
		dc.SetPen(m_pnThickRed);
		dc.DrawLine(m_iTurnBlackX + m_lppntErrorLogo[0].x * SZ_TURN_LOGO, m_iTurnBlackY + m_lppntErrorLogo[0].y * SZ_TURN_LOGO, m_iTurnBlackX + m_lppntErrorLogo[1].x * SZ_TURN_LOGO, m_iTurnBlackY + m_lppntErrorLogo[1].y * SZ_TURN_LOGO);
		dc.DrawLine(m_iTurnBlackX + m_lppntErrorLogo[2].x * SZ_TURN_LOGO, m_iTurnBlackY + m_lppntErrorLogo[2].y * SZ_TURN_LOGO, m_iTurnBlackX + m_lppntErrorLogo[3].x * SZ_TURN_LOGO, m_iTurnBlackY + m_lppntErrorLogo[3].y * SZ_TURN_LOGO);
		dc.SetPen(m_pnThickGreen);
		dc.DrawLine(m_iTurnWhiteX + m_lppntCorrectLogo[0].x * SZ_TURN_LOGO, m_iTurnWhiteY + m_lppntCorrectLogo[0].y * SZ_TURN_LOGO, m_iTurnWhiteX + m_lppntCorrectLogo[1].x * SZ_TURN_LOGO, m_iTurnWhiteY + m_lppntCorrectLogo[1].y * SZ_TURN_LOGO);
		dc.DrawLine(m_iTurnWhiteX + m_lppntCorrectLogo[1].x * SZ_TURN_LOGO, m_iTurnWhiteY + m_lppntCorrectLogo[1].y * SZ_TURN_LOGO, m_iTurnWhiteX + m_lppntCorrectLogo[2].x * SZ_TURN_LOGO, m_iTurnWhiteY + m_lppntCorrectLogo[2].y * SZ_TURN_LOGO);
		break;
	default:
		break;
	}
}

void CPainter::m_fnDrawPrisoners(wxBufferedDC &dc)
{
	wxSize szText;
	wxString wxstrNumPrsn;
	dc.SetFont(m_fntTip);
	dc.SetTextForeground(*wxBLACK);
	dc.SetTextBackground(*wxWHITE);
	szText = dc.GetTextExtent(m_wxstrPrisoners);
	dc.DrawText(m_wxstrPrisoners, m_iPrisonerTipX - szText.x / 2, m_iPrisonerTipY);
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(*wxBLACK_BRUSH);
	dc.DrawCircle(m_lpiWrappedStonesX[0] - m_iPrisonerRadius * 2, m_iWrappedStonesY, m_iPrisonerRadius);
	dc.DrawCircle(m_lpiWrappedStonesX[0] + m_iPrisonerRadius * 2, m_iWrappedStonesY, m_iPrisonerRadius);
	dc.DrawCircle(m_lpiWrappedStonesX[0], m_iWrappedStonesY - m_iPrisonerRadius * 2, m_iPrisonerRadius);
	dc.DrawCircle(m_lpiWrappedStonesX[0], m_iWrappedStonesY + m_iPrisonerRadius * 2, m_iPrisonerRadius);
	dc.DrawCircle(m_lpiWrappedStonesX[1], m_iWrappedStonesY, m_iPrisonerRadius);
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawCircle(m_lpiWrappedStonesX[1] - m_iPrisonerRadius * 2, m_iWrappedStonesY, m_iPrisonerRadius);
	dc.DrawCircle(m_lpiWrappedStonesX[1] + m_iPrisonerRadius * 2, m_iWrappedStonesY, m_iPrisonerRadius);
	dc.DrawCircle(m_lpiWrappedStonesX[1], m_iWrappedStonesY - m_iPrisonerRadius * 2, m_iPrisonerRadius);
	dc.DrawCircle(m_lpiWrappedStonesX[1], m_iWrappedStonesY + m_iPrisonerRadius * 2, m_iPrisonerRadius);
	dc.DrawCircle(m_lpiWrappedStonesX[0], m_iWrappedStonesY, m_iPrisonerRadius);
	dc.SetPen(*wxRED_PEN);
	dc.DrawLine(m_lpiWrappedStonesX[0] + m_lppntErrorLogo[0].x * m_iPrisonerRadius / m_iGridSize, m_iWrappedStonesY + m_lppntErrorLogo[0].y * m_iPrisonerRadius / m_iGridSize, m_lpiWrappedStonesX[0] + m_lppntErrorLogo[1].x * m_iPrisonerRadius / m_iGridSize, m_iWrappedStonesY + m_lppntErrorLogo[1].y * m_iPrisonerRadius / m_iGridSize);
	dc.DrawLine(m_lpiWrappedStonesX[0] + m_lppntErrorLogo[2].x * m_iPrisonerRadius / m_iGridSize, m_iWrappedStonesY + m_lppntErrorLogo[2].y * m_iPrisonerRadius / m_iGridSize, m_lpiWrappedStonesX[0] + m_lppntErrorLogo[3].x * m_iPrisonerRadius / m_iGridSize, m_iWrappedStonesY + m_lppntErrorLogo[3].y * m_iPrisonerRadius / m_iGridSize);
	dc.DrawLine(m_lpiWrappedStonesX[1] + m_lppntErrorLogo[0].x * m_iPrisonerRadius / m_iGridSize, m_iWrappedStonesY + m_lppntErrorLogo[0].y * m_iPrisonerRadius / m_iGridSize, m_lpiWrappedStonesX[1] + m_lppntErrorLogo[1].x * m_iPrisonerRadius / m_iGridSize, m_iWrappedStonesY + m_lppntErrorLogo[1].y * m_iPrisonerRadius / m_iGridSize);
	dc.DrawLine(m_lpiWrappedStonesX[1] + m_lppntErrorLogo[2].x * m_iPrisonerRadius / m_iGridSize, m_iWrappedStonesY + m_lppntErrorLogo[2].y * m_iPrisonerRadius / m_iGridSize, m_lpiWrappedStonesX[1] + m_lppntErrorLogo[3].x * m_iPrisonerRadius / m_iGridSize, m_iWrappedStonesY + m_lppntErrorLogo[3].y * m_iPrisonerRadius / m_iGridSize);
	wxstrNumPrsn = wxString::Format(wxString("%d"), m_GameBoardManager.m_lpiPrisoners[0]);
	szText = dc.GetTextExtent(wxstrNumPrsn);
	dc.DrawText(wxstrNumPrsn, m_lpiWrappedStonesX[0] - szText.x / 2, m_iPrisonerNumY);
	wxstrNumPrsn = wxString::Format(wxString("%d"), m_GameBoardManager.m_lpiPrisoners[1]);
	szText = dc.GetTextExtent(wxstrNumPrsn);
	dc.DrawText(wxstrNumPrsn, m_lpiWrappedStonesX[1] - szText.x / 2, m_iPrisonerNumY);
}

void CPainter::m_fnDrawNoMoveChoice(wxBufferedDC &dc)
{
	wxSize szText;
	dc.SetFont(m_fntTip);
	dc.SetTextForeground(*wxBLACK);
	dc.SetTextBackground(*wxWHITE);
	szText = dc.GetTextExtent(m_wxstrPassTip);
	dc.DrawText(m_wxstrPassTip, m_iPassTipX - szText.x / 2, m_iNoMoveTipY);
	szText = dc.GetTextExtent(m_wxstrResignTip);
	dc.DrawText(m_wxstrResignTip, m_iResignTipX - szText.x / 2, m_iNoMoveTipY);
	dc.SetPen(m_pnBlackLinePen);
	dc.DrawLine(m_iPassTipX, m_iTipArrowTop, m_iPassTipX, m_iTipArrowBottom);
	dc.DrawLine(m_iResignTipX, m_iTipArrowTop, m_iResignTipX, m_iTipArrowBottom);
	dc.DrawBitmap(m_bmpOriginalPass, m_iPassTipX - m_bmpOriginalPass.GetWidth() / 2, m_iNoMoveLogoY - m_bmpOriginalPass.GetHeight() / 2);
	dc.DrawBitmap(m_bmpOriginalResign, m_iResignTipX - m_bmpOriginalResign.GetWidth() / 2, m_iNoMoveLogoY - m_bmpOriginalResign.GetHeight() / 2);
}

void CPainter::m_fnDrawProcess(wxBufferedDC &dc)
{
	wxSize szText;
	int iProgressLen, iCols, iRows, iCurX, iCurY, i;
	dc.SetFont(m_fntTip);
	dc.SetTextForeground(*wxBLACK);
	dc.SetTextBackground(*wxWHITE);
	szText = dc.GetTextExtent(m_wxstrProcessTip);
	dc.DrawText(m_wxstrProcessTip, m_iProcessTipX - szText.x / 2, m_iProcessTipY);
	iProgressLen = m_GameBoardManager.m_vecRecords.size();
	iCols = (iProgressLen + 24) / 25;
	iRows = 12 + (iCols % 2 * 2 - 1) * ((iProgressLen + 24) % 25 - 12);
	dc.SetPen(*wxBLACK_PEN);
	if (iCols > 0)
	{
		if (iCols % 2 == 0 && iRows != 24)
		{
			dc.DrawLine(m_iProgressGraphX + (iCols + 1) * m_iGridSize / 2, m_iProgressGraphY + m_iGridSize * 12, m_iProgressGraphX + (iCols + 1) * m_iGridSize / 2, m_iProgressGraphY + m_iGridSize * iRows / 2);
		}
		if (iCols % 2 == 1 && iRows != 0)
		{
			dc.DrawLine(m_iProgressGraphX + (iCols + 1) * m_iGridSize / 2, m_iProgressGraphY, m_iProgressGraphX + (iCols + 1) * m_iGridSize / 2, m_iProgressGraphY + m_iGridSize * iRows / 2);
		}
		for (i = 0; i < iCols; i += 2)
		{
			dc.DrawLine(m_iProgressGraphX + (i + 1) * m_iGridSize / 2, m_iProgressGraphY, m_iProgressGraphX + (i + 2) * m_iGridSize / 2, m_iProgressGraphY);
		}
		if (iCols > 1)
		{
			for (i = 1; i < iCols; ++i)
			{
				dc.DrawLine(m_iProgressGraphX + (i + 1) * m_iGridSize / 2, m_iProgressGraphY, m_iProgressGraphX + (i + 1) * m_iGridSize / 2, m_iProgressGraphY + m_iGridSize * 12);
			}
			for (i = 1; i < iCols; i += 2)
			{
				dc.DrawLine(m_iProgressGraphX + (i + 1) * m_iGridSize / 2, m_iProgressGraphY + m_iGridSize * 12, m_iProgressGraphX + (i + 2) * m_iGridSize / 2, m_iProgressGraphY + m_iGridSize * 12);
			}
		}
	}
	if (iProgressLen > 0)
	{
		for (i = 0; i < iProgressLen; ++i)
		{
			iCurX = (i + 25) / 25;
			iCurY = 12 + (iCurX % 2 * 2 - 1) * (i % 25 - 12);
			switch (m_GameBoardManager.m_vecRecords[i].stone_color)
			{
			case SC_BLACK:
				dc.SetBrush(*wxBLACK_BRUSH);
				break;
			case SC_WHITE:
				dc.SetBrush(*wxWHITE_BRUSH);
				break;
            default:
                break;
			}
			if (i == m_GameBoardManager.m_iStepPos - 1)
			{
				dc.SetBrush(*wxGREEN_BRUSH);
			}
			dc.DrawCircle(m_iProgressGraphX + (iCurX + 1) * m_iGridSize / 2, m_iProgressGraphY + iCurY * m_iGridSize / 2, m_iGridSize / 8);
		}
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
				dc.DrawBitmap(m_bmpScaledBlackStone, m_iBoardLeft + m_iGridSize * (i / 19) - m_iGridSize / 2, m_iBoardTop + m_iGridSize * (i % 19) - m_iGridSize / 2, true);
			}
			else if ((*iterVisitor)->stone_color == SC_WHITE)
			{
				dc.DrawBitmap(m_bmpScaledWhiteStone, m_iBoardLeft + m_iGridSize * (i / 19) - m_iGridSize / 2, m_iBoardTop + m_iGridSize * (i % 19) - m_iGridSize / 2, true);
			}
		}
	}
}


void CPainter::m_fnDrawRecentMove(wxBufferedDC &dc)
{
	CGameBase::ExtendMove *lpemRecentMove;
	wxString wxstrIndex;
	wxSize szStringSize;
	if (m_GameBoardManager.m_iStepPos > 0)
	{
		lpemRecentMove = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos - 1]);
		if (lpemRecentMove->x >= 0 && lpemRecentMove->x < 19 && lpemRecentMove->y >= 0 && lpemRecentMove->y < 19)
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
				wxstrIndex = wxString::Format(wxString("%d"), m_GameBoardManager.m_iStepPos);
				szStringSize = dc.GetTextExtent(wxstrIndex);
				dc.DrawText(wxstrIndex, m_iBoardLeft + lpemRecentMove->x * m_iGridSize - szStringSize.x / 2, m_iBoardTop + lpemRecentMove->y * m_iGridSize - szStringSize.y / 2);
			}
			else
			{
				if (lpemRecentMove->stone_color == SC_BLACK)
				{
					dc.SetPen(m_pnWhiteLinePen);
				}
				else if (lpemRecentMove->stone_color == SC_WHITE)
				{
					dc.SetPen(m_pnBlackLinePen);
				}
				dc.DrawPolygon(3, m_lppntRecentMoveLogo, m_iBoardLeft + lpemRecentMove->x * m_iGridSize, m_iBoardTop + lpemRecentMove->y * m_iGridSize);
				dc.DrawPolygon(3, m_lppntRecentMoveLogo + 3, m_iBoardLeft + lpemRecentMove->x * m_iGridSize, m_iBoardTop + lpemRecentMove->y * m_iGridSize);
			}
		}
	}
}

void CPainter::m_fnDrawAnalyze(wxBufferedDC &dc, int x, int y)
{
	int iMaxVisit, i, nRouteLen;
	CGameBase::BoardPoint *lpbpLearningPoint;
	StoneColor scTest;
	CGameBase::BasePosition *lpbpTest;
	std::vector<CGameBase::BoardPoint*>::iterator iterBoardVisitor;
	CGameBase::BoardPoint *lpbpDraw;
	wxString wxstrMark;
	wxSize szStringSize;
	bool bPass;
	if (((x >= 0 && x < 19 && y >= 0 && y < 19) || (x == 19 && y == 0)) && m_GameBoardManager.m_fnPoint(x, y)->visits > 0)
	{
		lpbpLearningPoint = m_GameBoardManager.m_fnPoint(x, y);
		if (lpbpLearningPoint->pv_len > 0)
		{
			nRouteLen = min(lpbpLearningPoint->pv_len, m_lpAnalyzeSlider->GetValue());
			dc.SetFont(m_fntStep);
			scTest = m_GameBoardManager.m_scTurnColor;
			lpbpTest = lpbpLearningPoint->pv;
			for (i = 0; i < nRouteLen; ++i)
			{
				bPass = (lpbpTest->x == 19 && lpbpTest->y == 0);
				if (bPass || (lpbpTest->x >= 0 && lpbpTest->x < 19 && lpbpTest->y >= 0 && lpbpTest->y < 19))
				{
					if (i < 26)
					{
						wxstrMark = wxString::Format(wxString("%c"), (i + 'a'));
					}
					else
					{
						wxstrMark = wxString::Format(wxString("%c"), (i + 'A'));
					}
					szStringSize = dc.GetTextExtent(wxstrMark);
					if (scTest == SC_BLACK)
					{
						if (bPass)
						{
							dc.DrawBitmap(m_bmpScaledBlackStone, m_iPassTipX - m_iGridSize / 2, m_iNoMoveLogoY - m_iGridSize / 2, true);
						}
						else
						{
							dc.DrawBitmap(m_bmpScaledBlackStone, m_iBoardLeft + m_iGridSize * (lpbpTest->x) - m_iGridSize / 2, m_iBoardTop + m_iGridSize * (lpbpTest->y) - m_iGridSize / 2, true);
						}
						dc.SetTextBackground(*wxBLACK);
						dc.SetTextForeground(*wxWHITE);
					}
					if (scTest == SC_WHITE)
					{
						if (bPass)
						{
							dc.DrawBitmap(m_bmpScaledWhiteStone, m_iPassTipX - m_iGridSize / 2, m_iNoMoveLogoY - m_iGridSize / 2, true);
						}
						else
						{
							dc.DrawBitmap(m_bmpScaledWhiteStone, m_iBoardLeft + m_iGridSize * (lpbpTest->x) - m_iGridSize / 2, m_iBoardTop + m_iGridSize * (lpbpTest->y) - m_iGridSize / 2, true);
						}
						dc.SetTextBackground(*wxWHITE);
						dc.SetTextForeground(*wxBLACK);
					}
					if (bPass)
					{
						dc.DrawText(wxstrMark, m_iPassTipX - szStringSize.x / 2, m_iNoMoveLogoY - szStringSize.y / 2);
					}
					else
					{
						dc.DrawText(wxstrMark, m_iBoardLeft + lpbpTest->x * m_iGridSize - szStringSize.x / 2, m_iBoardTop + lpbpTest->y * m_iGridSize - szStringSize.y / 2);
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
					if (x == 19 && y == 0)
					{
						dc.DrawCircle(m_iPassTipX, m_iNoMoveLogoY, m_iGridSize / 2);
						wxstrMark = wxString::Format(wxString("%d.%d"), lpbpDraw->win_rate / 100, lpbpDraw->win_rate % 100);
						szStringSize = dc.GetTextExtent(wxstrMark);
						dc.DrawText(wxstrMark, m_iPassTipX - szStringSize.x / 2, m_iNoMoveLogoY - szStringSize.y * 5 / 6);
						wxstrMark = wxString::Format(wxString("%d"), lpbpDraw->visits);
						szStringSize = dc.GetTextExtent(wxstrMark);
						dc.DrawText(wxstrMark, m_iPassTipX - szStringSize.x / 2, m_iNoMoveLogoY - szStringSize.y / 6);
					}
					else
					{
						dc.DrawCircle(m_iBoardLeft + m_iGridSize * x, m_iBoardTop + m_iGridSize * y, m_iGridSize / 2);
						wxstrMark = wxString::Format(wxString("%d.%d"), lpbpDraw->win_rate / 100, lpbpDraw->win_rate % 100);
						szStringSize = dc.GetTextExtent(wxstrMark);
						dc.DrawText(wxstrMark, m_iBoardLeft + m_iGridSize * x - szStringSize.x / 2, m_iBoardTop + m_iGridSize * y - szStringSize.y * 5 / 6);
						wxstrMark = wxString::Format(wxString("%d"), lpbpDraw->visits);
						szStringSize = dc.GetTextExtent(wxstrMark);
						dc.DrawText(wxstrMark, m_iBoardLeft + m_iGridSize * x - szStringSize.x / 2, m_iBoardTop + m_iGridSize * y - szStringSize.y / 6);
					}
				}
			}
		}
	}
}
