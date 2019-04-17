#include "CLZInquirer.h"
CLZInquirer::CLZInquirer()
{
	m_lpOutputStream = 0;
	m_bAcceptChange = true;
}

void CLZInquirer::m_fnChangeLZBoardSize()
{
	wxString wxstrCommand = wxString::Format(wxString("boardsize %d\n"), nBoardSize);
	if (m_lpOutputStream != NULL)
	{
		m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
	}
}

void CLZInquirer::m_fnClearLZBoard()
{
	if (m_lpOutputStream != NULL)
	{
		m_lpOutputStream->Write("clear_board\n", 12);
	}
}

void CLZInquirer::m_fnSetLZHandicap()
{
	wxString wxstrCommand = wxString::Format(wxString("fixed_handicap %d\n"), m_GameBoardManager.m_nHandicap);
	if (m_lpOutputStream != NULL)
	{
		m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
	}
}


void CLZInquirer::m_fnSetThinkingTime()
{
	wxString wxstrCommand = wxString::Format(wxString("time_settings 0 %d 1\n"), m_iThinkingTime);
	if (m_lpOutputStream != NULL)
	{
		m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
	}
}

void CLZInquirer::m_fnSendMoveInfo(CGameBase::ExtendMove *lpMove)
{
	char lpstrCommand[16] = { '\0' };
	if (m_lpOutputStream != 0)
	{
		strcpy(lpstrCommand, "play ");
		lpMove->export_move(lpstrCommand + 5);
		strcat(lpstrCommand, "\n");
		m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
	}
}


void CLZInquirer::m_fnAppendGameRecord()
{
	CGameBase::ExtendMove *lpemVisitor;
	std::stack<CGameBase::ExtendMove*> stklpemStack;
	lpemVisitor = m_GameBoardManager.m_lpemCurrentMove;
	while (lpemVisitor != &(m_GameBoardManager.m_emBlankMove))
	{
		stklpemStack.push(lpemVisitor);
		lpemVisitor = lpemVisitor->parent;
	}
	while (!stklpemStack.empty())
	{
		lpemVisitor = stklpemStack.top();
		stklpemStack.pop();
		m_fnSendMoveInfo(lpemVisitor);
	}
}


void CLZInquirer::m_fnJumpTo(int iNewStep)
{
	char *lpstrCommand = (char*)"undo\n";
	if (m_bAcceptChange && iNewStep <= (m_GameBoardManager.m_lpemCurrentMove->step + m_GameBoardManager.m_lpemCurrentMove->depth))
	{
		m_fnResetAnalyze();
		while (m_GameBoardManager.m_lpemCurrentMove->step < iNewStep && m_GameBoardManager.OnRedoMove())
		{
			m_fnSendMoveInfo(m_GameBoardManager.m_lpemCurrentMove);
		}
		while (m_GameBoardManager.m_lpemCurrentMove->step > iNewStep && m_GameBoardManager.OnBackMove())
		{
			if (m_lpOutputStream != 0)
			{
				m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
			}
		}
	}
}

void CLZInquirer::m_fnResetAnalyze()
{
	m_GameBoardManager.m_bAcceptAnalyze = false;
	m_GameBoardManager.OnClearAnalyze();
}


void CLZInquirer::m_fnBackward()
{
	char *lpstrCommand = (char*)"undo\n";
	if (m_bAcceptChange && m_GameBoardManager.OnBackMove())
	{
		m_fnResetAnalyze();
		if (m_lpOutputStream != 0)
		{
			m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
		}
	}
}

void CLZInquirer::m_fnForward(CGameBase::ExtendMove *lpemMove)
{
	CGameBase::ExtendMove *lpemNew;
	if (m_bAcceptChange && m_GameBoardManager.OnRedoMove(lpemMove))
	{
		m_fnResetAnalyze();
		lpemNew = m_GameBoardManager.m_lpemCurrentMove;
		m_fnSendMoveInfo(lpemNew);
	}
}



void CLZInquirer::m_fnInquireMove()
{
	char lpstrCommand[16] = { '\0' };
	if (m_lpOutputStream != 0)
	{
		strcpy(lpstrCommand, "genmove ");
		switch (m_GameBoardManager.m_scTurnColor)
		{
		case SC_BLACK:
			strcat(lpstrCommand, " b\n");
			break;
		case SC_WHITE:
			strcat(lpstrCommand, " w\n");
			break;
		default:
			break;
		}
		m_bAcceptChange = false;
		m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
	}
}

void CLZInquirer::m_fnInquireResult()
{
	char lpstrCommand[] = "final_score\n";
	if (m_lpOutputStream != 0)
	{
		m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
	}
}


void CLZInquirer::m_fnInquireAnalyze()
{
	wxString wxstrCommand;
	if (m_iAnalyzeInterval > 0 && m_lpOutputStream != 0)
	{
		wxstrCommand = wxString("lz-analyze ") + wxString::Format(wxString("%d"), m_iAnalyzeInterval) + wxString("\n");
		m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
	}
}

void CLZInquirer::m_fnNotify()
{
	if (m_lpOutputStream != 0)
	{
		m_lpOutputStream->Write("\n", 1);
	}
}

