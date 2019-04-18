#include <fstream>
#include "CLZReceiver.h"
#include <fstream>

#define horizonal_coord_range(x) (((x) >= 'A' && (x) <= 'H') || ((x) >= 'a' && (x) <= 'h') || ((x) >= 'J' && (x) <= 'T') || ((x) >= 'j' && (x) <= 't'))
#define recognizable_char(x) (((x) == '=') || ((x) == '+') || ((x) == '.') || ((x) >= '0' && (x) <= '9') || ((x) >= 'a' && (x) <= 'z') || ((x) >= 'A' && (x) <= 'Z'))
CLZReceiver::CLZReceiver(): wxThread()
{
}

wxThread::ExitCode CLZReceiver::Entry()
{
    char lpstrBuffer[1024];
    char lpstrMessage[16];
    int i;
    std::vector<CGameBase::BasePosition>::iterator iterAnalyzing;
    i = 0;
    m_bKeepLoop = true;
    while (m_bKeepLoop)
    {
        m_lpInputStream->Read(lpstrBuffer + i, 1);
        if (recognizable_char(lpstrBuffer[i]))
        {
            ++i;
        }
        else
        {
            if (m_bRefresh && (lpstrBuffer[i] == '\r' || lpstrBuffer[i] == '\n'))
            {
				m_lpCanvas->Refresh();
            }
            m_bRefresh = false;
            if (i > 0)
            {
                lpstrBuffer[i] = '\0';
                strcpy(lpstrMessage, lpstrBuffer);
                i = 0;
                m_fnApplyMessage(lpstrMessage);
            }
        }
    }
    return wxThread::ExitCode(0);
}

void CLZReceiver::m_fnApplyMessage(char *lpstrMessage)
{
    CGameBase::BasePosition bpNewMove;
    DATA_TYPE dtDataType;
    bpNewMove.x = bpNewMove.y = -1;
    dtDataType = m_fnClassifyCommand(lpstrMessage);
    switch (dtDataType)
    {
    case DT_DIGIT:
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
				m_lpCanvas->m_AnalyzeMutex.Lock();
                m_lpbpAnalyzing->prior = atoi(lpstrMessage);
				m_lpCanvas->m_AnalyzeMutex.Unlock();
            }
            break;
		case DT_LCB:
            if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing != NULL)
            {
				m_lpCanvas->m_AnalyzeMutex.Lock();
                m_lpbpAnalyzing->lcb = atoi(lpstrMessage);
				m_lpCanvas->m_AnalyzeMutex.Unlock();
            }
        case DT_ORDER:
            if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing != NULL)
            {
				m_lpCanvas->m_AnalyzeMutex.Lock();
                m_lpbpAnalyzing->order = atoi(lpstrMessage);
				m_lpCanvas->m_AnalyzeMutex.Unlock();
            }
            break;
        default:
            break;
        }
        break;
    case DT_INFO:
        m_lpbpAnalyzing = NULL;
        break;
    case DT_COORDINATE:
        bpNewMove.import_position(lpstrMessage);
        switch (m_dtStatus)
        {
        case DT_EQUAL:
			if (m_lpCanvas->m_GameBoardManager.m_iHandicapPutting < m_lpCanvas->m_GameBoardManager.m_nHandicap)
			{
				m_lpCanvas->m_GameBoardManager.OnAddHandicap(bpNewMove.x, bpNewMove.y);
				m_bRefresh = true;
			}
			else if (m_lpCanvas->m_GameBoardManager.OnAddMove(bpNewMove.x, bpNewMove.y))
			{
				if (m_lpCanvas->m_GameBoardManager.m_bAlive)
				{
					if (m_lpCanvas->m_GameStatusManager.m_fnInquireAI(m_lpCanvas->m_GameBoardManager.m_scTurnColor))
					{
						m_lpCanvas->m_fnInquireMove();
					}
				}
				else
				{
					if (m_lpCanvas->m_GameStatusManager.m_lpToolBar->GetToolState(ID_BLACK_DOG))
					{
						m_lpCanvas->m_GameStatusManager.m_lpToolBar->ToggleTool(ID_BLACK_DOG, false);
						m_lpCanvas->m_GameStatusManager.m_fnSetBlackDog();
					}
					if (m_lpCanvas->m_GameStatusManager.m_lpToolBar->GetToolState(ID_WHITE_DOG))
					{
						m_lpCanvas->m_GameStatusManager.m_lpToolBar->ToggleTool(ID_WHITE_DOG, false);
						m_lpCanvas->m_GameStatusManager.m_fnSetWhiteDog();
					} 
					if (bpNewMove.x == nBoardSize && bpNewMove.y == 0)
					{
						m_lpCanvas->m_fnInquireResult();
					}
					else 
					if (bpNewMove.x == nBoardSize && bpNewMove.y == 1)
					{
						m_lpCanvas->m_fnShowResignResult();
					}
				}
				m_bRefresh = true;
			}
			scLastMove = m_lpCanvas->m_GameBoardManager.m_scTurnColor;
			m_lpCanvas->m_bAcceptChange = true;
            break;
        case DT_MOVE:
			m_lpCanvas->m_AnalyzeMutex.Lock();
			if ((bpNewMove.x >= 0 && bpNewMove.x < nBoardSize && bpNewMove.y >= 0 && bpNewMove.y < nBoardSize) || (bpNewMove.x == nBoardSize && bpNewMove.y == 0))
			{
				m_lpbpAnalyzing = m_lpCanvas->m_GameBoardManager.m_fnPoint(bpNewMove.x, bpNewMove.y);
				if (m_lpbpAnalyzing->visits == 0)
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
			m_lpCanvas->m_AnalyzeMutex.Unlock();
            break;
        case DT_PV:
            if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing != NULL)
            {
				if (m_lpbpAnalyzing->pv_len < 64)
				{
					m_lpCanvas->m_AnalyzeMutex.Lock();
					m_lpbpAnalyzing->pv[m_lpbpAnalyzing->pv_len] = bpNewMove;
					++(m_lpbpAnalyzing->pv_len);
					m_lpCanvas->m_AnalyzeMutex.Unlock();
				}
            }
            m_bRefresh = true;
            break;
        default:
            break;
        }
        break;
    case DT_RESULT:
        m_lpCanvas->m_fnShowCountResult(lpstrMessage);
        break;
    case DT_PV:
		if (m_lpbpAnalyzing != NULL)
		{
			m_lpbpAnalyzing->pv_len = 0;
		}
        m_dtStatus = dtDataType;
        break;
    case DT_EQUAL:
        m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze = true;
		m_lpCanvas->m_GameStatusManager.m_fnEngineConfirmed();
        m_dtStatus = dtDataType;
        break;
    default:
        if (dtDataType != DT_UNKNOWN)
        {
            m_dtStatus = dtDataType;
        }
        break;
    }
}



CLZReceiver::DATA_TYPE CLZReceiver::m_fnClassifyCommand(char *lpstrCommand)
{
	int i, len;
	DATA_TYPE dtType;
	len = strlen(lpstrCommand);
	dtType = DT_DIGIT;
	for (i = 0; i < len; ++i)
	{
		if (lpstrCommand[i] < '0' || lpstrCommand[i] > '9')
		{
			dtType = DT_RESULT;
			break;
		}
	}
	if (dtType == DT_RESULT && !((lpstrCommand[0] == 'B' || lpstrCommand[0] == 'W') && lpstrCommand[1] == '+'))
	{
		dtType = DT_UNKNOWN;
	}
	if (dtType == DT_UNKNOWN)
	{
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
			else
			{
				dtType = DT_UNKNOWN;
			}
			break;
		case 3:
			if (strcmp(lpstrCommand, "lcb") == 0)
			{
				dtType = DT_LCB;
			}
			else if (horizonal_coord_range(lpstrCommand[0]))
			{
				if (lpstrCommand[1] == '1' && lpstrCommand[2] >= '0' && lpstrCommand[2] <= '9')
				{
					dtType = DT_COORDINATE;
				}
				else
				{
					dtType = DT_UNKNOWN;
				}
			}
			else
			{
				dtType = DT_UNKNOWN;
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
			else if (strcmp(lpstrCommand, "pass") == 0)
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
			else if (strcmp(lpstrCommand, "resign") == 0)
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
	}
	if (len > 0 && dtType == DT_UNKNOWN)
	{
		dtType = DT_UNKNOWN;
	}
	return dtType;
}
