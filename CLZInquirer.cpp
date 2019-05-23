#include "CLZInquirer.h"
CLZInquirer::CLZInquirer()
{
	m_lpGameStatusManager = new CGameStatusManager;
	m_lpOutputStream = NULL;
	m_bOccupied = false;
}

void CLZInquirer::m_fnLZApplyInquire(InquireInfo *lpiiInquireInfo)
{
	wxString wxstrCommand;
	char lpstrCommand[16];
	CGameBase::BaseMove bmMove;
	if (m_lpOutputStream != NULL)
	{
		switch (lpiiInquireInfo->itInquireType)
		{
		case IT_NAME:
			m_lpOutputStream->Write("name\n", 5);
			break;
		case IT_TIME_SETTINGS:
			wxstrCommand = wxString::Format(wxString("time_settings 0 %d 1\n"), m_iThinkingTime);
			m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
			break;
		case IT_CHANGE_BOARD_SIZE:
			wxstrCommand = wxString::Format(wxString("boardsize %d\n"), nBoardSize);
			m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
			break;
		case IT_HANDICAP:
			wxstrCommand = wxString::Format(wxString("fixed_handicap %d\n"), m_GameBoardManager.m_nHandicap);
			m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
			break;
		case IT_CLEAR_BOARD:
			m_lpOutputStream->Write("clear_board\n", 12);
			break;
		case IT_PLAY:
			bmMove.stone_color = lpiiInquireInfo->scColor;
			bmMove.x = lpiiInquireInfo->x;
			bmMove.y = lpiiInquireInfo->y;
			bmMove.export_move(lpstrCommand);
			wxstrCommand = wxString("play ") + wxString(lpstrCommand) + wxString('\n');
			m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
			break;
		case IT_GEN_MOVE:
			strcpy(lpstrCommand, "genmove ");
			switch (lpiiInquireInfo->scColor)
			{
			case SC_BLACK:
				strcat(lpstrCommand, " b\n");
				break;
			case SC_WHITE:
				strcat(lpstrCommand, " w\n");
				break;
			}
			m_lpOutputStream->Write(lpstrCommand, strlen(lpstrCommand));
			break;
		case IT_BACKWARD:
			m_lpOutputStream->Write("undo\n", 5);
			break;
		//case IT_RESULT:
		//	m_lpOutputStream->Write("final_score\n", 12);
		//	break;
		case IT_ANALYZE:
			if (m_lpGameStatusManager->m_fnAnalyzing())
			{
				wxstrCommand = wxString::Format(wxString("lz-analyze %d\n"), m_iAnalyzeInterval);
				m_lpOutputStream->Write(wxstrCommand.char_str(), wxstrCommand.length());
			}
			else
			{
				while (!m_quiiLZInquireQueue.empty() && m_quiiLZInquireQueue.front().itInquireType == IT_ANALYZE)
				{
					m_quiiLZInquireQueue.pop();
				}
			}
			break;
		case IT_INTERRUPT:
			m_lpOutputStream->Write("\n", 1);
			break;
		case IT_QUIT:
			m_lpOutputStream->Write("quit\n", 5);
			break;
		}
	}
}

void CLZInquirer::m_fnReleaseInquire()
{
	m_OccupyMutex.Lock();
	if (!m_quiiLZInquireQueue.empty())
	{
		m_quiiLZInquireQueue.pop();
	}
	m_bOccupied = false;
	m_OccupyMutex.Unlock();
}


void CLZInquirer::m_fnLZExecuteFirstInquire()
{
	m_OccupyMutex.Lock();
	if (!(m_bOccupied || m_quiiLZInquireQueue.empty()))
	{
		while (m_quiiLZInquireQueue.front().itInquireType == IT_ANALYZE && m_quiiLZInquireQueue.size() > 1)
		{
			if (m_quiiLZInquireQueue.back().itInquireType != IT_ANALYZE)
			{
				m_quiiLZInquireQueue.push(m_quiiLZInquireQueue.front());
			}
			m_quiiLZInquireQueue.pop();
		}
		if (m_quiiLZInquireQueue.front().itInquireType != IT_ANALYZE)
		{
			m_bOccupied = true;
		}
		m_fnLZApplyInquire(&(m_quiiLZInquireQueue.front()));
	}
	m_OccupyMutex.Unlock();
}

void CLZInquirer::m_fnLZInquireName()
{
	InquireInfo iiInquire;
	iiInquire.itInquireType = IT_NAME;
	m_quiiLZInquireQueue.push(iiInquire);
}

void CLZInquirer::m_fnLZSetThinkingTime()
{
	InquireInfo iiInquire;
	iiInquire.itInquireType = IT_TIME_SETTINGS;
	iiInquire.iGlobalTime = 0;
	iiInquire.iStepTime = m_iThinkingTime;
	iiInquire.iSteps = 1;
	m_quiiLZInquireQueue.push(iiInquire);
}

void CLZInquirer::m_fnLZChangeBoardSize(int iBoardSize)
{
	InquireInfo iiInquire;
	iiInquire.itInquireType = IT_CHANGE_BOARD_SIZE;
	iiInquire.iBoardSize = iBoardSize;
	m_quiiLZInquireQueue.push(iiInquire);
}

void CLZInquirer::m_fnLZClearBoard()
{
	InquireInfo iiInquire;
	iiInquire.itInquireType = IT_CLEAR_BOARD;
	m_quiiLZInquireQueue.push(iiInquire);
}

void CLZInquirer::m_fnLZSetHandicap()
{
	InquireInfo iiInquire;
	iiInquire.itInquireType = IT_HANDICAP;
	m_quiiLZInquireQueue.push(iiInquire);
}

void CLZInquirer::m_fnLZAppendMove(StoneColor scColor, int x, int y)
{
	InquireInfo iiInquire;
	iiInquire.itInquireType = IT_PLAY;
	iiInquire.scColor = scColor;
	iiInquire.x = x;
	iiInquire.y = y;
	m_quiiLZInquireQueue.push(iiInquire);

}

void CLZInquirer::m_fnLZInquireMove(StoneColor scColor)
{
	InquireInfo iiInquire;
	iiInquire.itInquireType = IT_GEN_MOVE;
	iiInquire.scColor = scColor;
	m_quiiLZInquireQueue.push(iiInquire);
}

//void CLZInquirer::m_fnLZInquireResult()
//{
//	InquireInfo iiInquire;
//	iiInquire.itInquireType = IT_RESULT;
//	m_quiiLZInquireQueue.push(iiInquire);
//}


void CLZInquirer::m_fnLZInquireAnalyze()
{
	InquireInfo iiInquire;
	iiInquire.itInquireType = IT_ANALYZE;
	m_quiiLZInquireQueue.push(iiInquire);
}


void CLZInquirer::m_fnLZReloadGameRecord()
{
	int iCurrentStep = m_GameBoardManager.m_lpemCurrentMove->step;
	m_fnLZClearBoard();
	m_GameBoardManager.OnJumpTo(0);
	if (m_GameBoardManager.m_nHandicap != 0)
	{
		m_GameBoardManager.OnClearHandicap();
		m_fnLZSetHandicap();
	}
	m_fnLZJumpTo(iCurrentStep);
	m_GameBoardManager.OnJumpTo(iCurrentStep);
}

void CLZInquirer::m_fnLZJumpTo(int iNewStep)
{
	InquireInfo iiInquire;
	CGameBase::ExtendMove *lpemVisitor;
	char *lpstrCommand = (char*)"undo\n";
	if (iNewStep != (m_GameBoardManager.m_lpemCurrentMove->step) && iNewStep <= (m_GameBoardManager.m_lpemCurrentMove->step + m_GameBoardManager.m_lpemCurrentMove->depth))
	{
		m_GameBoardManager.OnClearAnalyze();
		lpemVisitor = m_GameBoardManager.m_lpemCurrentMove;
		if (lpemVisitor->step < iNewStep)
		{
			iiInquire.itInquireType = IT_PLAY;
			while (lpemVisitor->step < iNewStep)
			{
				lpemVisitor = lpemVisitor->child;
				iiInquire.scColor = lpemVisitor->stone_color;
				iiInquire.x = lpemVisitor->x;
				iiInquire.y = lpemVisitor->y;
				m_quiiLZInquireQueue.push(iiInquire);
			}
		}
		if (lpemVisitor->step > iNewStep)
		{
			iiInquire.itInquireType = IT_BACKWARD;
			while (lpemVisitor->step > iNewStep)
			{
				m_quiiLZInquireQueue.push(iiInquire);
				lpemVisitor = lpemVisitor->parent;
			}
		}
	}
}

void CLZInquirer::m_fnLZForward(CGameBase::ExtendMove *lpemMove)
{
	InquireInfo iiInquire;
	if (lpemMove == NULL)
	{
		lpemMove = m_GameBoardManager.m_lpemCurrentMove->child;
	}
	if (lpemMove != NULL)
	{
		iiInquire.itInquireType = IT_PLAY;
		iiInquire.scColor = lpemMove->stone_color;
		iiInquire.x = lpemMove->x;
		iiInquire.y = lpemMove->y;
		m_quiiLZInquireQueue.push(iiInquire);
	}
}

void CLZInquirer::m_fnLZBackward()
{
	InquireInfo iiInquire;
	iiInquire.itInquireType = IT_BACKWARD;
	m_quiiLZInquireQueue.push(iiInquire);
}


