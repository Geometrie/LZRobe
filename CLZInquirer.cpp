#include "CLZInquirer.h"
CLZInquirer::CLZInquirer()
{
	m_lpOutputStream = 0;
	m_bAcceptChange = true;
}

void CLZInquirer::m_fnClearLZBoard()
{
	if (m_lpOutputStream != NULL)
	{
		m_lpOutputStream->Write("clear_board\n", 12);
	}
}


void CLZInquirer::m_fnSetThinkingTime()
{
	wxString wxstrCommand = wxString("time_settings 0 ") + wxString::Format(wxString("%d"), m_iThinkingTime) + wxString(" 1\n");
	m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
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
	int i;
	if (m_GameBoardManager.m_iStepPos > 0)
	{
		for (i = 0; i < m_GameBoardManager.m_iStepPos; ++i)
		{
			m_fnSendMoveInfo(&(m_GameBoardManager.m_vecRecords[i]));
		}
	}
}


void CLZInquirer::m_fnJumpTo(int iNewStep)
{
	CGameBase::ExtendMove *lpemNew;
	char *lpstrCommand = (char*)"undo\n";
	if (m_bAcceptChange && iNewStep <= int(m_GameBoardManager.m_vecRecords.size()))
	{
		m_fnRefreshAnalyze();
		while (m_GameBoardManager.m_iStepPos < iNewStep && m_GameBoardManager.OnRedoMove())
		{
			lpemNew = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos - 1]);
			m_fnSendMoveInfo(lpemNew);
		}
		while (m_GameBoardManager.m_iStepPos > iNewStep && m_GameBoardManager.OnBackMove())
		{
			if (m_lpOutputStream != 0)
			{
				m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
			}
		}
	}
}

void CLZInquirer::m_fnRefreshAnalyze()
{
	m_GameBoardManager.m_bAcceptAnalyze = false;
	m_GameBoardManager.OnClearAnalyze();
}


void CLZInquirer::m_fnBackward()
{
	char *lpstrCommand = (char*)"undo\n";
	if (m_bAcceptChange && m_GameBoardManager.OnBackMove())
	{
		m_fnRefreshAnalyze();
		if (m_lpOutputStream != 0)
		{
			m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
		}
	}
}

void CLZInquirer::m_fnForward()
{
	CGameBase::ExtendMove *lpemNew;
	if (m_bAcceptChange && m_GameBoardManager.OnRedoMove())
	{
		m_fnRefreshAnalyze();
		lpemNew = &(m_GameBoardManager.m_vecRecords[m_GameBoardManager.m_iStepPos - 1]);
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

