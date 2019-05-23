#include <fstream>
#include "CLZReceiver.h"
#include <fstream>
#define horizonal_coord_range(x) (((x) >= 'A' && (x) <= 'H') || ((x) >= 'a' && (x) <= 'h') || ((x) >= 'J' && (x) <= 'T') || ((x) >= 'j' && (x) <= 't'))
CLZReceiver::CLZReceiver(): wxThread()
{
}

wxThread::ExitCode CLZReceiver::Entry()
{
	int i, j;
    char lpstrBuffer[512], lpstrMessage[16], *lpstrNewLine;
    std::vector<CGameBase::BasePosition>::iterator iterAnalyzing;
	SEPARATE_TYPE stSeparateType;
	DATA_TYPE dtDataType;
	i = 0;
    m_lpInputStream->Read(lpstrBuffer, 512);
	if (lpstrBuffer[0] == '=')
	{
		lpstrBuffer[i] = '\0';
		i = 1;
		while (lpstrBuffer[i] == ' ')
		{
			++i;
		}
		lpstrNewLine = strchr(lpstrBuffer + i, '\n');
		if (lpstrNewLine != NULL)
		{
			*lpstrNewLine = '\0';
		}
		lpstrNewLine = strchr(lpstrBuffer + i, '\r');
		if (lpstrNewLine != NULL)
		{
			*lpstrNewLine = '\0';
		}
		m_lpCanvas->m_lpGameStatusManager->m_wxstrEngineName = wxString(lpstrBuffer + i);
		m_lpCanvas->m_lpGameStatusManager->m_fnEngineConfirmed();
		m_lpCanvas->m_fnReleaseInquire();
		m_lpCanvas->m_fnLZReloadGameRecord();
		m_lpCanvas->m_fnLZExecuteFirstInquire();
		m_bKeepLoop = true;
		i = 0;
	}
	else
	{
		m_bKeepLoop = false;
	}
	stSeparateType = ST_NO_SEPARATE;
	m_dtStatus = DT_NULL;
    i = 0;
    while (m_bKeepLoop)
    {
		m_lpInputStream->Read(lpstrBuffer + i, 1);
		while (m_lpInputStream->CanRead() && lpstrBuffer[i] != ' ' && lpstrBuffer[i] != '\r' && lpstrBuffer[i] != '\n')
		{
			++i;
			m_lpInputStream->Read(lpstrBuffer + i, 1);
		}
		if (lpstrBuffer[i] == ' ' || lpstrBuffer[i] == '\n' || lpstrBuffer[i] == '\r')
		{
			while (m_lpInputStream->CanRead() && (lpstrBuffer[i] == ' ' || lpstrBuffer[i] == '\r' || lpstrBuffer[i] == '\n'))
			{
				++i;
				m_lpInputStream->Read(lpstrBuffer + i, 1);
			}
			j = i - 1;
			stSeparateType = ST_SPACE;
			while (lpstrBuffer[j] == ' ' || lpstrBuffer[j] == '\n' || lpstrBuffer[j] == '\r' && j >= 0)
			{
				if (lpstrBuffer[j] == '\n' || lpstrBuffer[j] == '\r')
				{
					stSeparateType = ST_ENTER;
				}
				--j;
			}
			lpstrBuffer[j + 1] = '\0';
			strcpy(lpstrMessage, lpstrBuffer);
			if (lpstrBuffer[i] == ' ' || lpstrBuffer[i] == '\r' || lpstrBuffer[i] == '\n')
			{
				i = 0;
			}
			else
			{
				lpstrBuffer[0] = lpstrBuffer[i];
				i = 1;
			}
		}
		else
		{
			lpstrBuffer[i + 1] = '\0';
			strcpy(lpstrMessage, lpstrBuffer);
			stSeparateType = ST_ENTER;
			i = 0;
		}
		if (strlen(lpstrMessage) > 0)
		{
			dtDataType = m_fnClassifyCommand(lpstrMessage);
			switch (dtDataType)
			{
			case DT_RESULT:
				m_lpCanvas->m_fnShowCountResult();
				m_lpCanvas->m_fnReleaseInquire();
				m_lpCanvas->m_fnLZExecuteFirstInquire();
				m_dtStatus = DT_NULL;
				break;
			case DT_EQUAL:
				m_dtStatus = DT_EQUAL;
				m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze = true;
				if (stSeparateType == ST_ENTER)
				{
					m_fnResponse();
				}
				break;
			case DT_COORDINATE:
				m_fnApplyCoordinate(lpstrMessage);
				if (stSeparateType == ST_ENTER && m_dtStatus == DT_PV)
				{
					m_lpCanvas->m_AnalyzeMutex.Unlock();
					m_fnRefresh();
					m_dtStatus = DT_NULL;
				}
				break;
			case DT_DIGIT:
				m_fnApplyDigit(lpstrMessage);
				break;
			case DT_MOVE:
				if (m_dtStatus = DT_PV)
				{
					m_lpCanvas->m_AnalyzeMutex.Unlock();
				}
				m_dtStatus = DT_MOVE;
				break;
			case DT_INFO:
				m_lpbpAnalyzing = NULL;
				m_dtStatus = DT_INFO;
				break;
			case DT_VISITS:
				m_dtStatus = DT_VISITS;
				break;
			case DT_WINRATE:
				m_dtStatus = DT_WINRATE;
				break;
			case DT_PRIOR:
				m_dtStatus = DT_PRIOR;
				break;
			case DT_LCB:
				m_dtStatus = DT_LCB;
				break;
			case DT_ORDER:
				m_dtStatus = DT_ORDER;
				break;
			case DT_PV:
				if (m_lpbpAnalyzing != NULL)
				{
					m_lpCanvas->m_AnalyzeMutex.Lock();
					m_lpbpAnalyzing->pv_len = 0;
				}
				m_dtStatus = DT_PV;
				break;
			}
		}
    }
    return wxThread::ExitCode(0);
}

void CLZReceiver::m_fnRefresh()
{
	if (m_lpCanvas->m_quiiLZInquireQueue.empty())
	{
		m_lpCanvas->Refresh();
	}
	else
	{
		switch (m_lpCanvas->m_quiiLZInquireQueue.front().itInquireType)
		{
		case IT_PLAY:
		case IT_BACKWARD:
			break;
		default:
			m_lpCanvas->Refresh();
		}
	}
}


void CLZReceiver::m_fnResponse()
{
	switch (m_lpCanvas->m_quiiLZInquireQueue.front().itInquireType)
	{
	case IT_ANALYZE:
		m_lpCanvas->m_fnReleaseInquire();
		m_dtStatus = DT_NULL;
		break;
	case IT_CLEAR_BOARD:
		m_lpCanvas->m_fnReleaseInquire();
		m_fnRefresh();
		m_lpCanvas->m_fnLZExecuteFirstInquire();
		m_dtStatus = DT_NULL;
		break;
	case IT_TIME_SETTINGS:
		m_lpCanvas->m_fnReleaseInquire();
		m_lpCanvas->m_fnLZExecuteFirstInquire();
		m_dtStatus = DT_NULL;
		break;
	case IT_CHANGE_BOARD_SIZE:
		nBoardSize = m_lpCanvas->m_quiiLZInquireQueue.front().iBoardSize;
		m_lpCanvas->m_GameBoardManager.m_fnChangeSize();
		m_lpCanvas->m_fnSetSize();
		m_lpCanvas->m_fnReleaseInquire();
		m_fnRefresh();
		m_lpCanvas->m_fnLZExecuteFirstInquire();
		m_dtStatus = DT_NULL;
		break;
	case IT_PLAY:
		m_lpCanvas->m_fnReleaseInquire();
		if (m_lpCanvas->m_lpGameStatusManager->m_fnInquireAI(m_lpCanvas->m_GameBoardManager.m_scTurnColor))
		{
			m_lpCanvas->m_fnLZInquireMove(m_lpCanvas->m_GameBoardManager.m_scTurnColor);
		}
		if (m_lpCanvas->m_lpGameStatusManager->m_fnAnalyzing())
		{
			m_lpCanvas->m_fnLZInquireAnalyze();
		}
		m_lpCanvas->m_fnLZExecuteFirstInquire();
		m_dtStatus = DT_NULL;
		break;
	case IT_BACKWARD:
		if (m_lpCanvas->m_lpGameStatusManager->m_fnAnalyzing())
		{
			m_lpCanvas->m_fnLZInquireAnalyze();
		}
		m_lpCanvas->m_fnReleaseInquire();
		m_lpCanvas->m_fnLZExecuteFirstInquire();
		m_dtStatus = DT_NULL;
		break;
	case IT_QUIT:
		m_bKeepLoop = false;
		m_lpCanvas->m_fnReleaseInquire();
		m_dtStatus = DT_NULL;
		break;
	}
}


void CLZReceiver::m_fnApplyCoordinate(char *lpstrMessage)
{
	CGameBase::BasePosition bpNew;
	CGameBase::BoardPoint **lplpbpSearch;
	bpNew.import_position(lpstrMessage);
	switch (m_dtStatus)
	{
	case DT_EQUAL:
		switch (m_lpCanvas->m_quiiLZInquireQueue.front().itInquireType)
		{
		case IT_HANDICAP:
			m_lpCanvas->m_GameBoardManager.OnAddHandicap(bpNew.x, bpNew.y);
			if (m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == m_lpCanvas->m_GameBoardManager.m_nHandicap)
			{
				m_lpCanvas->m_fnReleaseInquire();
				m_fnRefresh();
				m_lpCanvas->m_fnLZExecuteFirstInquire();
				m_dtStatus = DT_NULL;
			}
			break;
		case IT_GEN_MOVE:
			m_lpCanvas->m_fnReleaseInquire();
			if (m_lpCanvas->m_GameBoardManager.DoublePass(bpNew.x, bpNew.y))
			{
				m_lpCanvas->m_lpGameStatusManager->m_lpToolBar->ToggleTool(ID_BLACK_DOG, false);
				m_lpCanvas->m_lpGameStatusManager->m_fnSetBlackDog();
				m_lpCanvas->m_lpGameStatusManager->m_lpToolBar->ToggleTool(ID_WHITE_DOG, false);
				m_lpCanvas->m_lpGameStatusManager->m_fnSetWhiteDog();
				m_lpCanvas->m_fnLZReloadGameRecord();
			}
			else if (m_lpCanvas->m_GameBoardManager.Resign(bpNew.x, bpNew.y))
			{
				m_lpCanvas->m_fnShowResignResult();
				m_lpCanvas->m_lpGameStatusManager->m_lpToolBar->ToggleTool(ID_BLACK_DOG, false);
				m_lpCanvas->m_lpGameStatusManager->m_fnSetBlackDog();
				m_lpCanvas->m_lpGameStatusManager->m_lpToolBar->ToggleTool(ID_WHITE_DOG, false);
				m_lpCanvas->m_lpGameStatusManager->m_fnSetWhiteDog();
				m_lpCanvas->m_fnLZReloadGameRecord();
			}
			else
			{
				m_lpCanvas->m_GameBoardManager.OnAddMove(bpNew.x, bpNew.y);
				if (m_lpCanvas->m_lpGameStatusManager->m_fnInquireAI(m_lpCanvas->m_GameBoardManager.m_scTurnColor))
				{
					m_lpCanvas->m_fnLZInquireMove(m_lpCanvas->m_GameBoardManager.m_scTurnColor);
				}
			}
			m_fnRefresh();
			m_lpCanvas->m_fnLZExecuteFirstInquire();
			m_dtStatus = DT_NULL;
			break;
		}
		break;
	case DT_PV:
		if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing != NULL)
		{
			if (m_lpbpAnalyzing->pv_len < 64)
			{
				m_lpbpAnalyzing->pv[m_lpbpAnalyzing->pv_len] = bpNew;
				++(m_lpbpAnalyzing->pv_len);
			}
		}
		break;
	case DT_MOVE:
		if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && (bpNew.x >= 0 && bpNew.x < nBoardSize && bpNew.y >= 0 && bpNew.y < nBoardSize) || (bpNew.x == nBoardSize && bpNew.y == 0))
		{
			m_lpbpAnalyzing = m_lpCanvas->m_GameBoardManager.m_fnPoint(bpNew.x, bpNew.y);
			for (lplpbpSearch = m_lpCanvas->m_GameBoardManager.m_lpAnalyzingStones; lplpbpSearch != m_lpCanvas->m_GameBoardManager.m_lpAnalyzingEnd; ++lplpbpSearch)
			{
				if (*lplpbpSearch == m_lpbpAnalyzing)
				{
					break;
				}
			}
			if (lplpbpSearch == m_lpCanvas->m_GameBoardManager.m_lpAnalyzingEnd)
			{
				if (m_lpCanvas->m_GameBoardManager.m_lpAnalyzingEnd - m_lpCanvas->m_GameBoardManager.m_lpAnalyzingStones < 64)
				{
					*(m_lpCanvas->m_GameBoardManager.m_lpAnalyzingEnd) = m_lpbpAnalyzing;
					++(m_lpCanvas->m_GameBoardManager.m_lpAnalyzingEnd);
				}
				else
				{
					m_lpbpAnalyzing = NULL;
				}
			}
		}
		else
		{
			m_lpbpAnalyzing = NULL;
		}
		break;
	}
}



void CLZReceiver::m_fnApplyDigit(char *lpstrMessage)
{
	switch (m_dtStatus)
	{
	case DT_VISITS:
		if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing != NULL)
		{
			m_lpCanvas->m_AnalyzeMutex.Lock();
			m_lpbpAnalyzing->visits = atoi(lpstrMessage);
			m_lpCanvas->m_AnalyzeMutex.Unlock();
		}
		break;
	case DT_WINRATE:
		if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing != NULL)
		{
			m_lpCanvas->m_AnalyzeMutex.Lock();
			m_lpbpAnalyzing->win_rate = atoi(lpstrMessage);
			m_lpCanvas->m_AnalyzeMutex.Unlock();
		}
		break;
	case DT_PRIOR:
		if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing != NULL)
		{
			m_lpbpAnalyzing->prior = atoi(lpstrMessage);
		}
		break;
	case DT_LCB:
		if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing != NULL)
		{
			m_lpbpAnalyzing->lcb = atoi(lpstrMessage);
		}
	case DT_ORDER:
		if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing != NULL)
		{
			m_lpbpAnalyzing->order = atoi(lpstrMessage);
		}
		break;
	}
}



CLZReceiver::DATA_TYPE CLZReceiver::m_fnClassifyCommand(char *lpstrCommand)
{
	int i, len;
	DATA_TYPE dtType;
	len = strlen(lpstrCommand);
	dtType = DT_NULL;
	switch (len)
	{
	case 1:
		if (strcmp(lpstrCommand, "=") == 0)
		{
			dtType = DT_EQUAL;
		}
		break;
	case 2:
		if (strcmp(lpstrCommand, "pv") == 0)
		{
			dtType = DT_PV;
		}
		else if (horizonal_coord_range(lpstrCommand[0]))
		{
			if (lpstrCommand[1] >= '1' && lpstrCommand[1] <= '9')
			{
				dtType = DT_COORDINATE;
			}
		}
		break;
	case 3:
		if (strcmp(lpstrCommand, "lcb") == 0)
		{
			dtType = DT_LCB;
		}
		else if (horizonal_coord_range(lpstrCommand[0]))
		{
			if ((lpstrCommand[1] == '1' || lpstrCommand[1] == '2') && lpstrCommand[2] >= '0' && lpstrCommand[2] <= '9')
			{
				dtType = DT_COORDINATE;
			}
		}
		break;
	case 4:
		if (strcmp(lpstrCommand, "info") == 0)
		{
			dtType = DT_INFO;
		}
		else if (strcmp(lpstrCommand, "move") == 0)
		{
			dtType = DT_MOVE;
		}
		else if (strcmp(lpstrCommand, "pass") == 0 || strcmp(lpstrCommand, "Pass") == 0 || strcmp(lpstrCommand, "PASS") == 0)
		{
			dtType = DT_COORDINATE;
		}
		break;
	case 5:
		if (strcmp(lpstrCommand, "order") == 0)
		{
			dtType = DT_ORDER;
		}
		else if (strcmp(lpstrCommand, "prior") == 0)
		{
			dtType = DT_PRIOR;
		}
		break;
	case 6:
		if (strcmp(lpstrCommand, "visits") == 0)
		{
			dtType = DT_VISITS;
		}
		else if (strcmp(lpstrCommand, "resign") == 0 || strcmp(lpstrCommand, "Resign") == 0 || strcmp(lpstrCommand, "RESIGN") == 0)
		{
			dtType = DT_COORDINATE;
		}
		break;
	case 7:
		if (strcmp(lpstrCommand, "winrate") == 0)
		{
			dtType = DT_WINRATE;
		}
	}
	if (len > 0 && dtType == DT_NULL)
	{
		dtType = DT_DIGIT;
		for (i = 0; i < len; ++i)
		{
			if (lpstrCommand[i] < '0' || lpstrCommand[i] > '9')
			{
				dtType = DT_NULL;
				break;
			}
		}
		if (dtType == DT_NULL && ((lpstrCommand[0] == 'B' || lpstrCommand[0] == 'W') && lpstrCommand[1] == '+' && (lpstrCommand[2] >= '0' && lpstrCommand[2] <= '9')))
		{
			dtType = DT_RESULT;
		}
	}
	return dtType;
}
