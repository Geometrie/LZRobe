#include "CPainter.h"

CPainter::CPainter(wxWindow *lpParent) : wxScrolledWindow(lpParent),
m_fntPass(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntStep(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntAnalyze(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntTip(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
m_fntBranch(wxSize(70, 70), wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD),
m_clrLightBlue(127, 127, 255),
m_clrLightGreen(127, 255, 127),
m_clrLightRed(255, 127, 127),
m_clrLightYellow(255, 255, 127),
m_clrMagenta(127, 0, 127),
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
	m_iBoardUnitSize = m_iGridSize = 25;
	m_ctBoardTick = CT_NULL;
}

void CPainter::m_fnSetSize()
{

	int i;
	double dblAngle;
	wxImage imagScalor;
	wxSize szClient;
	szClient = GetSize();
	m_iGridSize = szClient.GetHeight() / 20;
	m_iBoardUnitSize = szClient.GetHeight() / (nBoardSize + 1);
	m_iBoardLeft = X_GAMEBOARD * m_iGridSize + m_iBoardUnitSize;
	m_iBoardTop = Y_GAMEBOARD * m_iGridSize + m_iBoardUnitSize;
	m_iBoardRight = X_GAMEBOARD * m_iGridSize + nBoardSize * m_iBoardUnitSize;
	m_iBoardBottom = Y_GAMEBOARD * m_iGridSize + nBoardSize * m_iBoardUnitSize;
	m_iBackgroundLeft = m_iBoardLeft - m_iBoardUnitSize;
	m_iBackgroundTop = m_iBoardTop - m_iBoardUnitSize;
	m_iBackgroundSize = (nBoardSize + 1) * m_iBoardUnitSize;
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
		m_lppntRecentMoveLogo[i] = wxPoint(int(m_iBoardUnitSize * sin(dblAngle) / 2 + 0.5), int(m_iBoardUnitSize * cos(dblAngle) / 2 + 0.5));
		m_lppntRecentMoveLogo[i + 3] = wxPoint(-m_lppntRecentMoveLogo[i].x, -m_lppntRecentMoveLogo[i].y);
	}
	m_pnBlackLinePen.SetWidth(m_iGridSize / 16);
	m_pnWhiteLinePen.SetWidth(m_iGridSize / 16);
	m_fntPass.SetPixelSize(wxSize(m_iGridSize * 4, m_iGridSize * 8));
	m_fntAnalyze.SetPixelSize(wxSize(m_iBoardUnitSize / 6, m_iBoardUnitSize / 2));
	m_fntStep.SetPixelSize(wxSize(m_iBoardUnitSize * 1 / 4, m_iBoardUnitSize * 5 / 8));
	m_fntTip.SetPixelSize(wxSize(m_iGridSize * 2 / 5, m_iGridSize));
	m_fntBranch.SetPixelSize(wxSize(m_iBoardUnitSize * 2 / 5, m_iBoardUnitSize));
	imagScalor = m_bmpOriginalBlackStone.ConvertToImage();
	imagScalor.Rescale(m_iBoardUnitSize, m_iBoardUnitSize);
	imagScalor.SetMaskColour(255, 255, 255);
	m_bmpScaledBlackStone = wxBitmap(imagScalor);
	imagScalor.Clear();
	imagScalor = m_bmpOriginalWhiteStone.ConvertToImage();
	imagScalor.Rescale(m_iBoardUnitSize, m_iBoardUnitSize);
	imagScalor.SetMaskColour(255, 255, 255);
	m_bmpScaledWhiteStone = wxBitmap(imagScalor);
	imagScalor.Clear();
	SetScrollbars(m_iGridSize, m_iGridSize, 40, 20);
	Refresh();
}


void CPainter::m_fnDrawCoordinates(wxDC &dc)
{
	int i;
	wxString wxstrTick;
	wxSize wxszStringSize;
	const  char *lplpUpperLetterTick[] = { "A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
	const char *lplpLowerLetterTick[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y" };
	const char *lplpNumTick[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25"};
	const char *lplpNumTickReverse[] = { "25", "24", "23", "22", "21", "20", "19", "18", "17", "16", "15", "14", "13", "12", "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1" };
	const char **lplpXTick, **lplpYTick;
	lplpXTick = NULL;
	lplpYTick = NULL;
	switch (m_ctBoardTick)
	{
	case CT_NET:
		lplpXTick = lplpLowerLetterTick;
		lplpYTick = lplpNumTick;
		break;
	case CT_NUM:
		lplpXTick = lplpNumTick;
		lplpYTick = lplpNumTick;
		break;
	case CT_SGF:
		lplpXTick = lplpLowerLetterTick;
		lplpYTick = lplpLowerLetterTick;
		break;
	case CT_GTP:
		lplpXTick = lplpUpperLetterTick;
		lplpYTick = lplpNumTickReverse + (25 - nBoardSize);
		break;
	}
	if (lplpXTick != NULL)
	{
		dc.SetFont(m_fntStep);
		for (i = 0; i < nBoardSize; ++i)
		{
			wxstrTick = wxString(lplpXTick[i]);
			wxszStringSize = dc.GetTextExtent(wxstrTick);
			dc.DrawText(wxstrTick, m_iBoardLeft + m_iBoardUnitSize * i - wxszStringSize.x / 2, m_iBoardTop - m_iBoardUnitSize / 2 - wxszStringSize.y / 2);
			dc.DrawText(wxstrTick, m_iBoardLeft + m_iBoardUnitSize * i - wxszStringSize.x / 2, m_iBoardBottom + m_iBoardUnitSize / 2 - wxszStringSize.y / 2);
		}
	}
	if (lplpYTick != NULL)
	{
		dc.SetFont(m_fntStep);
		for (i = 0; i < nBoardSize; ++i)
		{
			wxstrTick = wxString(lplpYTick[i]);
			wxszStringSize = dc.GetTextExtent(wxstrTick);
			dc.DrawText(wxstrTick, m_iBoardLeft - m_iBoardUnitSize / 2 - wxszStringSize.x / 2, m_iBoardTop + m_iBoardUnitSize * i - wxszStringSize.y / 2);
			dc.DrawText(wxstrTick, m_iBoardRight + m_iBoardUnitSize / 2 - wxszStringSize.x / 2, m_iBoardTop + m_iBoardUnitSize * i - wxszStringSize.y / 2);
		}
	}
}


void CPainter::m_fnDrawGameBoard(wxDC &dc)
{
	int i;
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.SetBrush(m_brGameBoard);
	dc.DrawRectangle(m_iBackgroundLeft, m_iBackgroundTop, m_iBackgroundSize, m_iBackgroundSize);
	dc.SetPen(m_pnBlackLinePen);
	for (i = 0; i < nBoardSize; ++i)
	{
		dc.DrawLine(m_iBoardLeft + m_iBoardUnitSize * i, m_iBoardTop, m_iBoardLeft + m_iBoardUnitSize * i, m_iBoardBottom);
	}
	for (i = 0; i < nBoardSize; ++i)
	{
		dc.DrawLine(m_iBoardLeft, m_iBoardTop + m_iBoardUnitSize * i, m_iBoardRight, m_iBoardTop + m_iBoardUnitSize * i);
	}
	dc.SetBrush(*wxBLACK_BRUSH);
	if (nBoardSize == 19)
	{
		for (i = 0; i < 9; ++i)
		{
			dc.DrawCircle(m_iBoardLeft + m_iGridSize * ((i % 3) * 6 + 3), m_iBoardTop + m_iGridSize * ((i / 3) * 6 + 3), m_iGridSize / 6);
		}
	}
}

void CPainter::m_fnDrawPass(wxDC &dc)
{
	wxSize szStringSize;
	if (m_GameBoardManager.m_lpemCurrentMove != &(m_GameBoardManager.m_emBlankMove))
	{
		if (m_GameBoardManager.m_lpemCurrentMove->x == nBoardSize && m_GameBoardManager.m_lpemCurrentMove->y == 0)
		{
			dc.SetFont(m_fntPass);
			szStringSize = dc.GetTextExtent(m_wxstrPass);
			dc.SetTextBackground(*wxWHITE);
			dc.SetTextForeground(*wxLIGHT_GREY);
			dc.DrawText(m_wxstrPass, (m_iBoardLeft + m_iBoardRight - szStringSize.x) / 2, (m_iBoardTop + m_iBoardBottom) / 2 - szStringSize.y * 2 / 3);
		}
	}
}


void CPainter::m_fnDrawMoveTurn(wxDC &dc)
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

void CPainter::m_fnDrawPrisoners(wxDC &dc)
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

void CPainter::m_fnDrawNoMoveChoice(wxDC &dc)
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

void CPainter::m_fnDrawProcess(wxDC &dc)
{
	wxSize szText;
	int iProgressLen, iCols, iRows, iCurX, iCurY, i;
	CGameBase::ExtendMove *lpemMoveVisitor;
	dc.SetFont(m_fntTip);
	dc.SetTextForeground(*wxBLACK);
	dc.SetTextBackground(*wxWHITE);
	szText = dc.GetTextExtent(m_wxstrProcessTip);
	dc.DrawText(m_wxstrProcessTip, m_iProcessTipX - szText.x / 2, m_iProcessTipY);
	iProgressLen = m_GameBoardManager.m_lpemCurrentMove->step + m_GameBoardManager.m_lpemCurrentMove->depth;
	iCols = (iProgressLen + 24) / 25;
	iRows = 12 + (iCols % 2 * 2 - 1) * ((iProgressLen + 24) % 25 - 12);
	dc.SetPen(*wxBLACK_PEN);
	if (iCols > 0)
	{
		if (iCols > 21)
		{
			iCols = 21;
		}
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
	if (m_GameBoardManager.m_emBlankMove.branch > 1)
	{
		if (m_GameBoardManager.m_nHandicap != 0)
		{
			dc.SetBrush(m_brLightRed);
		}
		else
		{
			dc.SetBrush(m_brLightBlue);
		}
		dc.DrawCircle(m_iProgressGraphX + m_iGridSize / 2, m_iProgressGraphY, m_iGridSize / 8);
	}
	else if (m_GameBoardManager.m_nHandicap != 0)
	{
		dc.SetBrush(*wxBLACK_BRUSH);
		dc.DrawCircle(m_iProgressGraphX + m_iGridSize / 2, m_iProgressGraphY, m_iGridSize / 8);
	}
	if (iProgressLen > 0)
	{
		lpemMoveVisitor = m_GameBoardManager.m_lpemCurrentMove;
		while (lpemMoveVisitor != &(m_GameBoardManager.m_emBlankMove))
		{
			i = lpemMoveVisitor->step - 1;
			if (i < 525)
			{
				iCurX = (i + 25) / 25;
				iCurY = 12 + (iCurX % 2 * 2 - 1) * (i % 25 - 12);
				switch (lpemMoveVisitor->stone_color)
				{
				case SC_BLACK:
					if (lpemMoveVisitor->branch == 1)
					{
						dc.SetBrush(*wxBLACK_BRUSH);
					}
					else
					{
						dc.SetBrush(m_brLightRed);
					}
					break;
				case SC_WHITE:
					if (lpemMoveVisitor->branch == 1)
					{
						dc.SetBrush(*wxWHITE_BRUSH);
					}
					else
					{
						dc.SetBrush(m_brLightBlue);
					}
					break;
				}
				if (lpemMoveVisitor == m_GameBoardManager.m_lpemCurrentMove)
				{
					dc.SetBrush(*wxGREEN_BRUSH);
				}
				dc.DrawCircle(m_iProgressGraphX + (iCurX + 1) * m_iGridSize / 2, m_iProgressGraphY + iCurY * m_iGridSize / 2, m_iGridSize / 8);
				lpemMoveVisitor = lpemMoveVisitor->parent;
			}
		}
		lpemMoveVisitor = m_GameBoardManager.m_lpemCurrentMove->child;
		while (lpemMoveVisitor != NULL)
		{
			i = lpemMoveVisitor->step - 1;
			if (i < 525)
			{
				iCurX = (i + 25) / 25;
				iCurY = 12 + (iCurX % 2 * 2 - 1) * (i % 25 - 12);
				switch (lpemMoveVisitor->stone_color)
				{
				case SC_BLACK:
					if (lpemMoveVisitor->branch <= 1)
					{
						dc.SetBrush(*wxBLACK_BRUSH);
					}
					else
					{
						dc.SetBrush(m_brLightRed);
					}
					break;
				case SC_WHITE:
					if (lpemMoveVisitor->branch <= 1)
					{
						dc.SetBrush(*wxWHITE_BRUSH);
					}
					else
					{
						dc.SetBrush(m_brLightBlue);
					}
					break;
				}
				dc.DrawCircle(m_iProgressGraphX + (iCurX + 1) * m_iGridSize / 2, m_iProgressGraphY + iCurY * m_iGridSize / 2, m_iGridSize / 8);
				lpemMoveVisitor = lpemMoveVisitor->child;
			}
			else
			{
				lpemMoveVisitor = NULL;
			}
		}
	}
}

void CPainter::m_fnDrawStones(wxDC &dc)
{
	CGameBase::ExtendMove *lpemMoveVisitor;
	CGameBase::BoardPoint *lpbpPoint;
	int i, x, y;
	if (m_GameBoardManager.m_iHandicapPutting > 0)
	{
		for (i = 0; i < m_GameBoardManager.m_iHandicapPutting; ++i)
		{
			lpbpPoint = m_GameBoardManager.m_lplpbpHandicap[i];
			m_GameBoardManager.m_fnCoordinate(lpbpPoint, x, y);
			if (lpbpPoint->stone_color == SC_BLACK)
			{
				dc.DrawBitmap(m_bmpScaledBlackStone, m_iBoardLeft + x * m_iBoardUnitSize - m_iBoardUnitSize / 2, m_iBoardTop + y * m_iBoardUnitSize - m_iBoardUnitSize / 2, true);
			}
			else if (lpbpPoint->stone_color == SC_WHITE)
			{
				dc.DrawBitmap(m_bmpScaledWhiteStone, m_iBoardLeft + x * m_iBoardUnitSize - m_iBoardUnitSize / 2, m_iBoardTop + y * m_iBoardUnitSize - m_iBoardUnitSize / 2, true);
			}
		}
	}
	if (m_GameBoardManager.m_lpemCurrentMove != NULL)
	{
		lpemMoveVisitor = m_GameBoardManager.m_lpemCurrentMove;
		while (lpemMoveVisitor != &(m_GameBoardManager.m_emBlankMove))
		{
			if (lpemMoveVisitor->x >= 0 && lpemMoveVisitor->x < nBoardSize && lpemMoveVisitor->y >= 0 && lpemMoveVisitor->y < nBoardSize)
			{
				lpbpPoint = m_GameBoardManager.m_fnPoint(lpemMoveVisitor->x, lpemMoveVisitor->y);
				if (lpbpPoint->stone_color == SC_BLACK)
				{
					dc.DrawBitmap(m_bmpScaledBlackStone, m_iBoardLeft + lpemMoveVisitor->x * m_iBoardUnitSize - m_iBoardUnitSize / 2, m_iBoardTop + lpemMoveVisitor->y * m_iBoardUnitSize - m_iBoardUnitSize / 2, true);
				}
				else if (lpbpPoint->stone_color == SC_WHITE)
				{
					dc.DrawBitmap(m_bmpScaledWhiteStone, m_iBoardLeft + lpemMoveVisitor->x * m_iBoardUnitSize - m_iBoardUnitSize / 2, m_iBoardTop + lpemMoveVisitor->y * m_iBoardUnitSize - m_iBoardUnitSize / 2, true);
				}
			}
			lpemMoveVisitor = lpemMoveVisitor->parent;
		}
	}
}

void CPainter::m_fnDrawTerritory(wxDC &dc)
{
	CGameBase::BoardPoint *lpbpVisitor, *lpbpGameBoardEnd;
	int x, y;
	lpbpGameBoardEnd = m_GameBoardManager.m_lpbpGameBoard + nBoardSize * nBoardSize;
	for (lpbpVisitor = m_GameBoardManager.m_lpbpGameBoard; lpbpVisitor != lpbpGameBoardEnd; ++lpbpVisitor)
	{
		m_GameBoardManager.m_fnCoordinate(lpbpVisitor, x, y);
		switch (lpbpVisitor->stone_color)
		{
		case SC_BLACK:
			dc.DrawBitmap(m_bmpScaledBlackStone, m_iBoardLeft + x * m_iBoardUnitSize - m_iBoardUnitSize / 2, m_iBoardTop + y * m_iBoardUnitSize - m_iBoardUnitSize / 2, true);
			break;
		case SC_WHITE:
			dc.DrawBitmap(m_bmpScaledWhiteStone, m_iBoardLeft + x * m_iBoardUnitSize - m_iBoardUnitSize / 2, m_iBoardTop + y * m_iBoardUnitSize - m_iBoardUnitSize / 2, true);
			break;
		case SC_BLK_TER:
			dc.SetBrush(*wxBLACK_BRUSH);
			dc.DrawRectangle(m_iBoardLeft + x * m_iBoardUnitSize - m_iBoardUnitSize / 4, m_iBoardTop + y * m_iBoardUnitSize - m_iBoardUnitSize / 4, m_iBoardUnitSize / 2, m_iBoardUnitSize / 2);
			break;
		case SC_WHT_TER:
			dc.SetPen(*wxBLACK_PEN);
			dc.SetBrush(*wxWHITE_BRUSH);
			dc.DrawRectangle(m_iBoardLeft + x * m_iBoardUnitSize - m_iBoardUnitSize / 4, m_iBoardTop + y * m_iBoardUnitSize - m_iBoardUnitSize / 4, m_iBoardUnitSize / 2, m_iBoardUnitSize / 2);
			break;
		}
	}
}

void CPainter::m_fnDrawBranch(wxDC &dc)
{
	CGameBase::ExtendMove *lpemBranchVisitor;
	char cLabel;
	wxString wxstrLabel;
	wxSize wxszLabelSize;
	if (m_GameBoardManager.m_lpemCurrentMove->branch > 1)
	{
		cLabel = 'A';
		lpemBranchVisitor = m_GameBoardManager.m_lpemCurrentMove->child;
		while (lpemBranchVisitor != NULL)
		{
			wxstrLabel = wxString::Format(wxString("%c"), cLabel);
			dc.SetFont(m_fntBranch);
			dc.SetTextBackground(wxTransparentColour);
			dc.SetTextForeground(m_clrMagenta);
			wxszLabelSize = dc.GetTextExtent(wxstrLabel);
			if (lpemBranchVisitor->x == nBoardSize && lpemBranchVisitor->y == 0)
			{
				dc.DrawText(wxstrLabel, m_iPassTipX - wxszLabelSize.x / 2, m_iNoMoveLogoY - wxszLabelSize.y / 2);
			}
			else
			{
				dc.DrawText(wxstrLabel, m_iBoardLeft + lpemBranchVisitor->x * m_iBoardUnitSize - wxszLabelSize.x / 2, m_iBoardTop + lpemBranchVisitor->y * m_iBoardUnitSize - wxszLabelSize.y / 2);
			}
			lpemBranchVisitor = lpemBranchVisitor->shorter;
			++cLabel;
		}
	}
}

void CPainter::m_fnDrawRecentMove(wxDC &dc)
{
	CGameBase::ExtendMove *lpemRecentMove;
	wxString wxstrIndex;
	wxSize szStringSize;
	if (m_GameBoardManager.m_lpemCurrentMove != &(m_GameBoardManager.m_emBlankMove))
	{
		lpemRecentMove = m_GameBoardManager.m_lpemCurrentMove;
		if (lpemRecentMove->x >= 0 && lpemRecentMove->x < nBoardSize && lpemRecentMove->y >= 0 && lpemRecentMove->y < nBoardSize)
		{
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
				wxstrIndex = wxString::Format(wxString("%d"), lpemRecentMove->step);
				szStringSize = dc.GetTextExtent(wxstrIndex);
				dc.DrawText(wxstrIndex, m_iBoardLeft + lpemRecentMove->x * m_iBoardUnitSize - szStringSize.x / 2, m_iBoardTop + lpemRecentMove->y * m_iBoardUnitSize - szStringSize.y / 2);
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
				dc.SetBrush(*wxTRANSPARENT_BRUSH);
				dc.DrawPolygon(3, m_lppntRecentMoveLogo, m_iBoardLeft + lpemRecentMove->x * m_iBoardUnitSize, m_iBoardTop + lpemRecentMove->y * m_iBoardUnitSize);
				dc.DrawPolygon(3, m_lppntRecentMoveLogo + 3, m_iBoardLeft + lpemRecentMove->x * m_iBoardUnitSize, m_iBoardTop + lpemRecentMove->y * m_iBoardUnitSize);
			}
		}
	}
}

void CPainter::m_fnDrawAnalyze(wxDC &dc, int x, int y)
{
	int iMaxVisit, i, nRouteLen;
	CGameBase::BoardPoint *lpbpLearningPoint;
	StoneColor scTest;
	CGameBase::BasePosition *lpbpTest;
	CGameBase::BoardPoint**lplpbpAnalyzing;
	CGameBase::BoardPoint *lpbpDraw;
	wxString wxstrMark;
	wxSize szStringSize;
	bool bPass;
	const char *lplpcMarks[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", \
		"o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",\
		GRKLT_ALPHA, GRKLT_BETA, GRKLT_GAMMA, GRKLT_DELTA, GRKLT_EPSILON, GRKLT_ZETA,\
		GRKLT_ETA, GRKLT_THETA, GRKLT_IOTA, GRKLT_KAPPA, GRKLT_LAMBDA, GRKLT_MU, \
		GRKLT_NU, GRKLT_XI, GRKLT_OMICRON, GRKLT_PI, GRKLT_RHO, GRKLT_SIGMA, \
		GRKLT_TAU, GRKLT_UPSILON, GRKLT_PHI, GRKLT_KI, GRKLT_PSI, GRKLT_OMEGA};
	if (((x >= 0 && x < nBoardSize && y >= 0 && y < nBoardSize) || (x == nBoardSize && y == 0)) && m_GameBoardManager.m_fnPoint(x, y)->visits > 0)
	{
		lpbpLearningPoint = m_GameBoardManager.m_fnPoint(x, y);
		if (lpbpLearningPoint->pv_len > 0)
		{
			nRouteLen = min(lpbpLearningPoint->pv_len, m_lpGameStatusManager->m_lpAnalyzeSpinCtrl->GetValue());//min(lpbpLearningPoint->pv_len, m_lpAnalyzeSlider->GetValue());
			dc.SetFont(m_fntStep);
			scTest = m_GameBoardManager.m_scTurnColor;
			lpbpTest = lpbpLearningPoint->pv;
			for (i = 0; i < nRouteLen; ++i)
			{
				bPass = (lpbpTest->x == nBoardSize && lpbpTest->y == 0);
				if (bPass || (lpbpTest->x >= 0 && lpbpTest->x < nBoardSize && lpbpTest->y >= 0 && lpbpTest->y < nBoardSize))
				{
					wxstrMark = wxString(lplpcMarks[i]);
					szStringSize = dc.GetTextExtent(wxstrMark);
					if (scTest == SC_BLACK)
					{
						if (bPass)
						{
							dc.DrawBitmap(m_bmpScaledBlackStone, m_iPassTipX - m_iGridSize / 2, m_iNoMoveLogoY - m_iGridSize / 2, true);
						}
						else
						{
							dc.DrawBitmap(m_bmpScaledBlackStone, m_iBoardLeft + m_iBoardUnitSize * (lpbpTest->x) - m_iBoardUnitSize / 2, m_iBoardTop + m_iBoardUnitSize * (lpbpTest->y) - m_iBoardUnitSize / 2, true);
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
							dc.DrawBitmap(m_bmpScaledWhiteStone, m_iBoardLeft + m_iBoardUnitSize * (lpbpTest->x) - m_iBoardUnitSize / 2, m_iBoardTop + m_iBoardUnitSize * (lpbpTest->y) - m_iBoardUnitSize / 2, true);
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
						dc.DrawText(wxstrMark, m_iBoardLeft + lpbpTest->x * m_iBoardUnitSize - szStringSize.x / 2, m_iBoardTop + lpbpTest->y * m_iBoardUnitSize - szStringSize.y / 2);
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
		for (lplpbpAnalyzing = m_GameBoardManager.m_lpAnalyzingStones; lplpbpAnalyzing < m_GameBoardManager.m_lpAnalyzingEnd; ++lplpbpAnalyzing)
		{
			lpbpDraw = *lplpbpAnalyzing;
			if (lpbpDraw->visits > iMaxVisit)
			{
				iMaxVisit = lpbpDraw->visits;
			}
		}
		if (iMaxVisit > 0)
		{
			for (lplpbpAnalyzing = m_GameBoardManager.m_lpAnalyzingStones; lplpbpAnalyzing < m_GameBoardManager.m_lpAnalyzingEnd; ++lplpbpAnalyzing)
			{
				lpbpDraw = *lplpbpAnalyzing;
				if (lpbpDraw->visits > 0)
				{
					m_GameBoardManager.m_fnCoordinate(lpbpDraw, x, y);
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
					if (x == nBoardSize && y == 0)
					{
						dc.DrawCircle(m_iPassTipX, m_iNoMoveLogoY, m_iGridSize / 2);
					}
					else
					{
						dc.DrawCircle(m_iBoardLeft + m_iBoardUnitSize * x, m_iBoardTop + m_iBoardUnitSize * y, m_iGridSize / 2);
					}
				}
			}
			m_fnDrawBranch(dc);
			dc.SetFont(m_fntAnalyze);
			for (lplpbpAnalyzing = m_GameBoardManager.m_lpAnalyzingStones; lplpbpAnalyzing < m_GameBoardManager.m_lpAnalyzingEnd; ++lplpbpAnalyzing)
			{
				lpbpDraw = *lplpbpAnalyzing;
				if (lpbpDraw->visits > 0)
				{
					m_GameBoardManager.m_fnCoordinate(lpbpDraw, x, y);
					dc.SetTextForeground(*wxBLACK);
					dc.SetTextBackground(wxTransparentColour);
					if (x == nBoardSize && y == 0)
					{
						wxstrMark = wxString::Format(wxString("%d.%d"), lpbpDraw->win_rate / 100, lpbpDraw->win_rate % 100);
						szStringSize = dc.GetTextExtent(wxstrMark);
						dc.DrawText(wxstrMark, m_iPassTipX - szStringSize.x / 2, m_iNoMoveLogoY - szStringSize.y * 5 / 6);
						wxstrMark = wxString::Format(wxString("%d"), lpbpDraw->visits);
						szStringSize = dc.GetTextExtent(wxstrMark);
						dc.DrawText(wxstrMark, m_iPassTipX - szStringSize.x / 2, m_iNoMoveLogoY - szStringSize.y / 6);
					}
					else
					{
						wxstrMark = wxString::Format(wxString("%d.%d"), lpbpDraw->win_rate / 100, lpbpDraw->win_rate % 100);
						szStringSize = dc.GetTextExtent(wxstrMark);
						dc.DrawText(wxstrMark, m_iBoardLeft + m_iBoardUnitSize * x - szStringSize.x / 2, m_iBoardTop + m_iBoardUnitSize * y - szStringSize.y * 5 / 6);
						wxstrMark = wxString::Format(wxString("%d"), lpbpDraw->visits);
						szStringSize = dc.GetTextExtent(wxstrMark);
						dc.DrawText(wxstrMark, m_iBoardLeft + m_iBoardUnitSize * x - szStringSize.x / 2, m_iBoardTop + m_iBoardUnitSize * y - szStringSize.y / 6);
					}
				}
			}
		}
	}
}