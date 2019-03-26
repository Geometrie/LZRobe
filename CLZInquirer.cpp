#include "CLZInquirer.h"
CLZInquirer::CLZInquirer()
{
	m_lpOutputStream = 0;
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

