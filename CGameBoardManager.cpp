#include "CGameBoardManager.h"
CGameBoardManager::CGameBoardManager()
{
    m_scTurnColor = SC_BLACK;
    m_iStepPos = 0;
    m_bAlive = true;
    m_bAcceptAnalyze = true;
	m_lpiPrisoners[0] = m_lpiPrisoners[1] = 0;
}


CGameBoardManager::~CGameBoardManager()
{
    OnClearGameRecord();
}


void CGameBoardManager::m_fnRefreshStones()
{
	std::list<CGameBase::BoardPoint*>::iterator iterVisitor;
	if (m_lstExistingStones.size() > 0)
	{
		iterVisitor = m_lstExistingStones.begin();
		while (iterVisitor != m_lstExistingStones.end())
		{
			if (!((*iterVisitor)->stone_color == SC_BLACK || (*iterVisitor)->stone_color == SC_WHITE))
			{
				iterVisitor = m_lstExistingStones.erase(iterVisitor);
			}
			else
			{
				++iterVisitor;
			}
		}
	}
}


bool CGameBoardManager::OnTestMove(int x, int y)
{
    bool bLegal;
    std::vector<CGameBase::BoardPoint*> vecRemove;
    std::vector<CGameBase::BoardPoint*>::iterator iterRemoveVisitor;
    CGameBase::BasePosition bpTest;
    if ((x == -1 && y == -1) || (x == -2 && y == -2))
    {
        bLegal = true;
    }
    else
    {
        if (m_fnPoint(x, y)->stone_color == SC_NULL)
        {
            bLegal = m_fnIsLegalMove(m_scTurnColor, x, y, vecRemove);
            if (bLegal)
            {
                if (!m_vecRecords.empty() && vecRemove.size () == 1)
                {
                    if (m_vecRecords.rbegin()->vecRemoved.size() == 1)
                    {
                        bpTest = m_vecRecords.rbegin()->vecRemoved[0];
                        if (bpTest.x == x && bpTest.y == y)
                        {
                            bLegal = false;
                        }
                    }
                }
            }
        }
        else
        {
            bLegal = false;
        }
    }
    if (bLegal)
    {
        if (vecRemove.size() > 0)
        {
            vecRemove.clear();
        }
    }
    return bLegal;
}

bool CGameBoardManager::OnAddMove(int x, int y)
{
    bool bLegal;
    std::vector<CGameBase::BoardPoint*> vecRemove;
    std::vector<CGameBase::BoardPoint*>::iterator iterRemoveVisitor;
    CGameBase::BoardPoint *lpptCurrent;
    CGameBase::BasePosition bpTest;
    CGameBase::ExtendMove movNew;
    if (!m_bAlive)
    {
        bLegal = false;
    }
    else if ((x == 19 && y == 0) || (x == 19 && y == 1))
    {
        bLegal = true;
    }
    else
    {
        if (m_fnPoint(x, y)->stone_color == SC_NULL)
        {
            bLegal = m_fnIsLegalMove(m_scTurnColor, x, y, vecRemove);
            if (bLegal)
            {
                if (!m_vecRecords.empty() && vecRemove.size () == 1)
                {
                    if (m_vecRecords.rbegin()->vecRemoved.size() == 1)
                    {
                        bpTest = m_vecRecords.rbegin()->vecRemoved[0];
                        if (bpTest.x == x && bpTest.y == y)
                        {
                            bLegal = false;
                        }
                    }
                }
            }
        }
        else
        {
            bLegal = false;
        }
    }
    if (bLegal)
    {
        if (x >= 0 && x < 19 && y >= 0 && y < 19)
        {
            lpptCurrent = m_fnPoint(x, y);
            lpptCurrent->stone_color = m_scTurnColor;
			m_lstExistingStones.push_back(lpptCurrent);
        }
        if (x == 19 && y == 0 && m_vecRecords.size() > 0)
        {
            if (m_vecRecords.rbegin()->x == 19 && m_vecRecords.rbegin()->y == 0)
            {
                m_bAlive = false;
            }
        }
		if (x == 19 && y == 1)
		{
			m_bAlive = false;
		}
        movNew.x = x;
        movNew.y = y;
        movNew.stone_color = m_scTurnColor;
        m_scTurnColor = opposite_color(m_scTurnColor);
        if (vecRemove.size() > 0)
        {
            for (iterRemoveVisitor = vecRemove.begin(); iterRemoveVisitor != vecRemove.end(); ++iterRemoveVisitor)
            {
                (*iterRemoveVisitor)->stone_color = SC_NULL;
                bpTest.x = (int((*iterRemoveVisitor) - m_lpGameBoard)) / 19;
                bpTest.y = (int((*iterRemoveVisitor) - m_lpGameBoard)) % 19;
                movNew.vecRemoved.push_back(bpTest);
            }
            vecRemove.clear();
			m_fnRefreshStones();
        }
        m_vecRecords.push_back(movNew);
		switch (m_scTurnColor)
		{
		case SC_BLACK:
			m_lpiPrisoners[1] += int(movNew.vecRemoved.size());
			break;
		case SC_WHITE:
			m_lpiPrisoners[0] += int(movNew.vecRemoved.size());
			break;
		default:
			break;
		}
        movNew.vecRemoved.clear();
        m_iStepPos = int(m_vecRecords.size());
    }
    return bLegal;
}
bool CGameBoardManager::OnBackMove()
{
    bool bSucceed;
    std::vector<CGameBase::BasePosition>::iterator iterRemoveVisitor;
    CGameBase::ExtendMove *lpLastMove;
	CGameBase::BoardPoint *lpbpRemove;
    if (m_iStepPos > 0)
    {
        --m_iStepPos;
        lpLastMove = &(m_vecRecords[m_iStepPos]);
        m_scTurnColor = opposite_color(lpLastMove->stone_color);
        if (lpLastMove->x >= 0 && lpLastMove->x < 19 && lpLastMove->y >= 0 && lpLastMove->y < 19)
        {
            m_fnPoint(lpLastMove->x, lpLastMove->y)->stone_color = SC_NULL;
			m_fnRefreshStones();
        }
        if (lpLastMove->vecRemoved.size() > 0)
        {
			switch (lpLastMove->stone_color)
			{
			case SC_BLACK:
				m_lpiPrisoners[0] -= int(lpLastMove->vecRemoved.size());
				break;
			case SC_WHITE:
				m_lpiPrisoners[1] -= int(lpLastMove->vecRemoved.size());
				break;
			default:
				break;
			}
            for (iterRemoveVisitor = lpLastMove->vecRemoved.begin(); iterRemoveVisitor != lpLastMove->vecRemoved.end(); ++iterRemoveVisitor)
            {
				lpbpRemove = m_fnPoint(iterRemoveVisitor->x, iterRemoveVisitor->y);
				lpbpRemove->stone_color = m_scTurnColor;
				m_lstExistingStones.push_back(lpbpRemove);
            }
        }
        m_scTurnColor = lpLastMove->stone_color;
        bSucceed = true;
    }
    else
    {
        bSucceed = false;
    }
    return bSucceed;
}

bool CGameBoardManager::OnRedoMove()
{
    bool bSucceed;
    std::vector<CGameBase::BasePosition>::iterator iterRemoveVisitor;
	CGameBase::BoardPoint *lpbpCurrentPoint;
    CGameBase::ExtendMove *lpNextMove;
    if (m_iStepPos < int(m_vecRecords.size()))
    {
        lpNextMove = &(m_vecRecords[m_iStepPos]);
        ++m_iStepPos;
        if (lpNextMove->x >= 0 && lpNextMove->x < 19 && lpNextMove->y >= 0 && lpNextMove->y < 19)
        {
			lpbpCurrentPoint = m_fnPoint(lpNextMove->x, lpNextMove->y);
            lpbpCurrentPoint->stone_color = lpNextMove->stone_color;
			m_lstExistingStones.push_back(lpbpCurrentPoint);
        }
        if (lpNextMove->vecRemoved.size() > 0)
        {
			switch (lpNextMove->stone_color)
			{
			case SC_BLACK:
				m_lpiPrisoners[0] += int(lpNextMove->vecRemoved.size());
				break;
			case SC_WHITE:
				m_lpiPrisoners[1] += int(lpNextMove->vecRemoved.size());
				break;
			default:
				break;
			}
            for (iterRemoveVisitor = lpNextMove->vecRemoved.begin(); iterRemoveVisitor != lpNextMove->vecRemoved.end(); ++iterRemoveVisitor)
            {
                m_fnPoint(iterRemoveVisitor->x, iterRemoveVisitor->y)->stone_color = SC_NULL;
            }
			m_fnRefreshStones();
        }
        m_scTurnColor = opposite_color(lpNextMove->stone_color);
        bSucceed = true;
    }
    else
    {
        bSucceed = false;
    }
    return bSucceed;
}

bool CGameBoardManager::OnModifyGameRecord()
{
    bool bSucceed;
    int i;
    if (m_iStepPos < int(m_vecRecords.size()))
    {
        for (i = int(m_vecRecords.size()); i > m_iStepPos; --i)
        {
            m_vecRecords[i - 1].vecRemoved.clear();
            m_vecRecords.pop_back();
        }
        bSucceed = true;
    }
    else
    {
        bSucceed = false;
    }
    return bSucceed;
}

void CGameBoardManager::OnClearGameRecord()
{
    int i;
    if (m_vecRecords.size() > 0)
    {
        for (i = int(m_vecRecords.size()); i > 0; --i)
        {
            m_vecRecords[i - 1].vecRemoved.clear();
            m_vecRecords.pop_back();
        }
        if (m_iStepPos > 0)
        {
            for (i = 0; i < 361; ++i)
            {
                m_lpGameBoard[i].stone_color = SC_NULL;
            }
            m_iStepPos = 0;
        }
    }
    m_scTurnColor = SC_BLACK;
	m_lpiPrisoners[0] = m_lpiPrisoners[1] = 0;
    m_bAlive = true;
}

void CGameBoardManager::OnClearAnalyze()
{
    CGameBase::BoardPoint *lpbpCurrent;
	std::vector<CGameBase::BoardPoint*>::iterator iterVisitor;
	for (iterVisitor = m_vecAnalyzingStones.begin(); iterVisitor != m_vecAnalyzingStones.end(); ++iterVisitor)
	{
		lpbpCurrent = (*iterVisitor);
		lpbpCurrent->pv_len = 0;
		lpbpCurrent->visits = 0;
        lpbpCurrent->order = -1;
        lpbpCurrent->win_rate = -1;
	}
	m_vecAnalyzingStones.clear();
}

void CGameBoardManager::OnReadSgf(std::ifstream &ifs)
{
    char c;
    int x, y;
    StoneColor stone_color;
    while (!ifs.eof())
    {
        ifs.get(c);
        if (c == ';')
        {
            ifs.get(c);
            if (c == 'B' || c == 'W')
            {
                if (c == 'B')
                {
                    stone_color = SC_BLACK;
                }
                else if (c == 'W')
                {
                    stone_color = SC_WHITE;
                }
                ifs.get(c);
                if (c == '[')
                {
                    ifs.get(c);
                    if (c >= 'a' && c <= 's')
                    {
                        x = c - 'a';
                        ifs.get(c);
                        if (c >= 'a' && c <= 's')
                        {
                            y = c - 'a';
                            ifs.get(c);
                            if (c == ']')
                            {
                                m_scTurnColor = stone_color;
                                OnAddMove(x, y);
                            }
                        }
                    }
                }
            }
        }
    }
}
