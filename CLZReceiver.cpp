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
    m_lpemNew = NULL;
    m_lpemLast = NULL;
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
                if (m_lpemNew != NULL)
                {
                    m_lpCanvas->m_fnRefreshStep(m_lpemNew);
                    m_lpemNew = NULL;
                }
                if (m_lpemLast != NULL)
                {
                    m_lpCanvas->m_fnRefreshStep(m_lpemLast);
                    m_lpemLast = NULL;
                }
                if (m_lpCanvas->m_GameBoardManager.m_vecAnalyzingStones.size() > 0)
                {
					m_lpCanvas->m_fnRefreshBoardRange(0, 0, 18, 18);
                }
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

CLZReceiver::DATA_TYPE CLZReceiver::m_fnClassifyCommand(char *lpstrCommand)
{
    int i, len;
    len = strlen(lpstrCommand);
    DATA_TYPE dtType;
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
            if (horizonal_coord_range(lpstrCommand[0]))
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
                dtType = DT_RESIGN;
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
            if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing->stone_color == SC_NULL)
            {
                m_lpbpAnalyzing->visits = atoi(lpstrMessage);
            }
            break;
        case DT_WINRATE:
            if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing->stone_color == SC_NULL)
            {
                m_lpbpAnalyzing->win_rate = atoi(lpstrMessage);
            }
            break;
        case DT_PRIOR:
            if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing->stone_color == SC_NULL)
            {
                m_lpbpAnalyzing->prior = atoi(lpstrMessage);
            }
            break;
        case DT_ORDER:
            if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing->stone_color == SC_NULL)
            {
                m_lpbpAnalyzing->order = atoi(lpstrMessage);
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
            if (m_lpCanvas->m_GameBoardManager.OnAddMove(bpNewMove.x, bpNewMove.y))
            {
                m_lpemNew = &(m_lpCanvas->m_GameBoardManager.m_vecRecords[m_lpCanvas->m_GameBoardManager.m_iStepPos - 1]);
                if (m_lpCanvas->m_GameBoardManager.m_iStepPos > 1)
                {
                    m_lpemLast = &(m_lpCanvas->m_GameBoardManager.m_vecRecords[m_lpCanvas->m_GameBoardManager.m_iStepPos - 2]);
                }
                if (m_lpCanvas->m_GameBoardManager.m_bAlive)
                {
                    if (m_lpCanvas->m_GameStatusManager.m_fnInquireAI(m_lpCanvas->m_GameBoardManager.m_scTurnColor))//((bBlackDog && m_lpCanvas->m_GameBoardManager.m_scTurnColor == SC_BLACK) || (bWhiteDog && m_lpCanvas->m_GameBoardManager.m_scTurnColor == SC_WHITE))
                    {
                        m_lpCanvas->m_fnInquireMove();
                    }
                    else if (m_lpCanvas->m_GameStatusManager.m_lpToolBar->GetToolState(ID_ANALYZE))
                    {
                        m_lpCanvas->m_fnInquireAnalyze();
                    }
                }
                else
                {
                    m_lpCanvas->m_fnInquireResult();
                }
                m_bRefresh = true;
            }
            break;
        case DT_MOVE:
			if (bpNewMove.x >= 0 && bpNewMove.x < 19 && bpNewMove.y >= 0 && bpNewMove.y < 19)
			{
				m_lpbpAnalyzing = m_lpCanvas->m_GameBoardManager.m_fnPoint(bpNewMove.x, bpNewMove.y);
				if (m_lpbpAnalyzing->visits == 0)
				{
					m_lpCanvas->m_GameBoardManager.m_vecAnalyzingStones.push_back(m_lpbpAnalyzing);
				}
			}
			else
			{
				m_lpbpAnalyzing = NULL;
			}
            break;
        case DT_PV:
            if (m_lpCanvas->m_GameBoardManager.m_bAcceptAnalyze && m_lpbpAnalyzing->stone_color == SC_NULL)
            {
				if (m_lpbpAnalyzing->pv_len < 32)
				{
					m_lpbpAnalyzing->pv[m_lpbpAnalyzing->pv_len] = bpNewMove;
					++(m_lpbpAnalyzing->pv_len);
				}
            }
            m_bRefresh = true;
            break;
        default:
            break;
        }
        break;
    case DT_RESIGN:
        if (m_lpCanvas->m_GameStatusManager.m_fnInquireAI(SC_BLACK))
        {
            m_lpCanvas->m_GameStatusManager.m_lpToolBar->ToggleTool(ID_BLACK_DOG, false);
        }
        if (m_lpCanvas->m_GameStatusManager.m_fnInquireAI(SC_WHITE))
        {
            m_lpCanvas->m_GameStatusManager.m_lpToolBar->ToggleTool(ID_WHITE_DOG, false);
        }
        m_lpCanvas->m_fnShowResignResult();
        break;
    case DT_RESULT:
        m_lpCanvas->m_fnShowCountResult(lpstrMessage);
        break;
    case DT_PV:
		m_lpbpAnalyzing->pv_len = 0;
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


