#include "CGameManager.h"
CGameManager::CGameManager()
{
    m_scTurnColor = CGameBase::SC_BLACK;
    m_iStepPos = 0;
    m_bAlive = true;
    m_bAcceptAnalyze = true;
}

void CGameManager::m_fnSelectStoneBlock(int x, int y, std::vector<CGameBase::BasePosition> &vecBlock)
{
    CGameBase::StoneColor stone_color;
    CGameBase::BasePosition bpTest;
    CGameBase::BoardPoint *lpbpTest;
    int i;
    std::queue<CGameBase::BasePosition> qubpQueue;
    std::vector<CGameBase::BasePosition>::iterator iterBlockVisitor;
    if (x >= 0 && x < 19 && y >= 0 && y < 19)
    {
        bpTest.x = x;
        bpTest.y = y;
        lpbpTest = m_fnPoint(x, y);
        stone_color = lpbpTest->stone_color;
        lpbpTest->mark += 1;
        qubpQueue.push(bpTest);
        vecBlock.push_back(bpTest);
        while (!qubpQueue.empty())
        {
            bpTest = qubpQueue.front();
            qubpQueue.pop();
            x = bpTest.x;
            y = bpTest.y;
            for (i = 0; i < 4; ++i)
            {
                bpTest.x = x + (1 - i % 2) * (1 - (i / 2) * 2);
                bpTest.y = y + (i % 2) * (1 - (i / 2) * 2);
                if (bpTest.x >= 0 && bpTest.x < 19 && bpTest.y >= 0 && bpTest.y < 19)
                {
                    lpbpTest = m_fnPoint(bpTest.x, bpTest.y);
                    if (lpbpTest->stone_color == stone_color && (lpbpTest->mark & 1) == 0)
                    {
                        lpbpTest->mark += 1;
                        vecBlock.push_back(bpTest);
                        qubpQueue.push(bpTest);
                    }
                }
            }
        }
        for (iterBlockVisitor = vecBlock.begin(); iterBlockVisitor != vecBlock.end(); ++iterBlockVisitor)
        {
            lpbpTest = m_fnPoint(iterBlockVisitor->x, iterBlockVisitor->y);
            lpbpTest->mark -= 1;
        }
    }
}

CGameManager::~CGameManager()
{
    OnClearGameRecord();
}

int CGameManager::m_fnCountLiberty(std::vector<CGameBase::BasePosition> &vecBlock)
{
    std::vector<CGameBase::BasePosition>::iterator iterBlockVisitor;
    std::vector<CGameBase::BoardPoint*> vecLiberties;
    std::vector<CGameBase::BoardPoint*>::iterator iterLibertyVisitor;
    CGameBase::BoardPoint *lpbpTest;
    int i, nCount, x, y;
    for (iterBlockVisitor = vecBlock.begin(); iterBlockVisitor != vecBlock.end(); ++iterBlockVisitor)
    {
        for (i = 0; i < 4; ++i)
        {
            x = iterBlockVisitor->x + (1 - i % 2) * (1 - (i / 2) * 2);
            y = iterBlockVisitor->y + (i % 2) * (1 - (i / 2) * 2);
            if (x >= 0 && x < 19 && y >= 0 && y < 19)
            {
                lpbpTest = m_fnPoint(x, y);
                if (lpbpTest->stone_color == CGameBase::SC_NULL && (lpbpTest->mark & 1) == 0)
                {
                    lpbpTest->mark += 1;
                    vecLiberties.push_back(lpbpTest);
                }
            }
        }
    }
    nCount = vecLiberties.size();
    if (nCount > 0)
    {
        for (iterLibertyVisitor = vecLiberties.begin(); iterLibertyVisitor != vecLiberties.end(); ++iterLibertyVisitor)
        {
            (*iterLibertyVisitor)->mark -= 1;
        }
        vecLiberties.clear();
    }
    return nCount;
}

bool CGameManager::m_fnIsLegalMove(CGameBase::StoneColor stone_color, int x, int y, std::vector<CGameBase::BoardPoint*> &vecRemove)
{
    bool bLegal;
    int i, nLiberty;
    CGameBase::BoardPoint *lpbpTest, *lpbpSelect;
    CGameBase::BasePosition bpTest;
    std::vector<CGameBase::BasePosition> vecBlock;
    std::vector<CGameBase::BasePosition>::iterator iterBlockVisitor;
    std::vector<CGameBase::BoardPoint*>::iterator iterMarkVisitor;
    std::vector<CGameBase::BoardPoint*> vecLink;
    bLegal = false;
    if (x == -1 && y == -1)
    {
        bLegal = true;
    }
    for (i = 0; i < 4; ++i)
    {
        bpTest.x = x + (1 - i % 2) * (1 - (i / 2) * 2);
        bpTest.y = y + (i % 2) * (1 - (i / 2) * 2);
        if (bpTest.x >= 0 && bpTest.x < 19 && bpTest.y >= 0 && bpTest.y < 19)
        {
            lpbpTest = m_fnPoint(bpTest.x, bpTest.y);
            if (lpbpTest->stone_color == CGameBase::SC_NULL)
            {
                bLegal = true;
            }
            else if ((lpbpTest->mark & 2) == 0)
            {
                m_fnSelectStoneBlock(bpTest.x, bpTest.y, vecBlock);
                nLiberty = m_fnCountLiberty(vecBlock);
                if ((lpbpTest->stone_color == stone_color) && (nLiberty > 1))
                {
                    bLegal = true;
                    for (iterBlockVisitor = vecBlock.begin(); iterBlockVisitor != vecBlock.end(); ++iterBlockVisitor)
                    {
                        lpbpSelect = m_fnPoint(iterBlockVisitor->x, iterBlockVisitor->y);
                        if ((lpbpSelect->mark & 2) == 0)
                        {
                            lpbpSelect->mark += 2;
                            vecLink.push_back(lpbpSelect);
                        }
                    }
                }
                if ((lpbpTest->stone_color != stone_color) && (nLiberty == 1))
                {
                    bLegal = true;
                    for (iterBlockVisitor = vecBlock.begin(); iterBlockVisitor != vecBlock.end(); ++iterBlockVisitor)
                    {
                        lpbpSelect = m_fnPoint(iterBlockVisitor->x, iterBlockVisitor->y);
                        if ((lpbpSelect->mark & 2) == 0)
                        {
                            lpbpSelect->mark += 2;
                            vecRemove.push_back(lpbpSelect);
                        }
                    }
                }
                vecBlock.clear();
            }
        }
    }
    if (vecRemove.size() > 0)
    {
        for (iterMarkVisitor = vecRemove.begin(); iterMarkVisitor != vecRemove.end(); ++iterMarkVisitor)
        {
            (*iterMarkVisitor)->mark -= 2;
        }
    }
    if (vecLink.size() > 0)
    {
        for (iterMarkVisitor = vecLink.begin(); iterMarkVisitor != vecLink.end(); ++iterMarkVisitor)
        {
            (*iterMarkVisitor)->mark -= 2;
        }
        vecLink.clear();
    }
    return bLegal;
}

bool CGameManager::OnTestMove(int x, int y)
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
        if (m_fnPoint(x, y)->stone_color == CGameBase::SC_NULL)
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

bool CGameManager::OnAddMove(int x, int y)
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
    else if ((x == -1 && y == -1))
    {
        bLegal = true;
    }
    else
    {
        if (m_fnPoint(x, y)->stone_color == CGameBase::SC_NULL)
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
        }
        if (x == -1 && y == -1 && m_vecRecords.size() > 0)
        {
            if (m_vecRecords.rbegin()->x == -1 && m_vecRecords.rbegin()->y == -1)
            {
                m_bAlive = false;
            }
        }
        movNew.x = x;
        movNew.y = y;
        movNew.stone_color = m_scTurnColor;
        m_scTurnColor = opposite_color(m_scTurnColor);
        if (vecRemove.size() > 0)
        {
            for (iterRemoveVisitor = vecRemove.begin(); iterRemoveVisitor != vecRemove.end(); ++iterRemoveVisitor)
            {
                (*iterRemoveVisitor)->stone_color = CGameBase::SC_NULL;
                bpTest.x = ((*iterRemoveVisitor) - m_lpGameBoard) / 19;
                bpTest.y = ((*iterRemoveVisitor) - m_lpGameBoard) % 19;
                movNew.vecRemoved.push_back(bpTest);
            }
            vecRemove.clear();
        }
        m_vecRecords.push_back(movNew);
        movNew.vecRemoved.clear();
        m_iStepPos =m_vecRecords.size();
    }
    return bLegal;
}
bool CGameManager::OnBackMove()
{
    bool bSucceed;
    std::vector<CGameBase::BasePosition>::iterator iterRemoveVisitor;
    CGameBase::ExtendMove *lpLastMove;
    if (m_iStepPos > 0)
    {
        --m_iStepPos;
        lpLastMove = &(m_vecRecords[m_iStepPos]);
        m_scTurnColor = opposite_color(lpLastMove->stone_color);
        if (lpLastMove->x >= 0 && lpLastMove->x < 19 && lpLastMove->y >= 0 && lpLastMove->y < 19)
        {
            m_fnPoint(lpLastMove->x, lpLastMove->y)->stone_color = CGameBase::SC_NULL;
        }
        if (lpLastMove->vecRemoved.size() > 0)
        {
            for (iterRemoveVisitor = lpLastMove->vecRemoved.begin(); iterRemoveVisitor != lpLastMove->vecRemoved.end(); ++iterRemoveVisitor)
            {
                m_fnPoint(iterRemoveVisitor->x, iterRemoveVisitor->y)->stone_color = m_scTurnColor;
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

bool CGameManager::OnRedoMove()
{
    bool bSucceed;
    std::vector<CGameBase::BasePosition>::iterator iterRemoveVisitor;
    CGameBase::ExtendMove *lpNextMove;
    if (m_iStepPos < int(m_vecRecords.size()))
    {
        lpNextMove = &(m_vecRecords[m_iStepPos]);
        ++m_iStepPos;
        if (lpNextMove->x >= 0 && lpNextMove->x < 19 && lpNextMove->y >= 0 && lpNextMove->y < 19)
        {
            m_fnPoint(lpNextMove->x, lpNextMove->y)->stone_color = lpNextMove->stone_color;
        }
        if (lpNextMove->vecRemoved.size() > 0)
        {
            for (iterRemoveVisitor = lpNextMove->vecRemoved.begin(); iterRemoveVisitor != lpNextMove->vecRemoved.end(); ++iterRemoveVisitor)
            {
                m_fnPoint(iterRemoveVisitor->x, iterRemoveVisitor->y)->stone_color = CGameBase::SC_NULL;
            }
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

bool CGameManager::OnModifyGameRecord()
{
    bool bSucceed;
    int i;
    if (m_iStepPos < int(m_vecRecords.size()))
    {
        for (i = m_vecRecords.size(); i > m_iStepPos; --i)
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
    m_bAlive = true;
    return bSucceed;
}

void CGameManager::OnClearGameRecord()
{
    int i;
    if (m_vecRecords.size() > 0)
    {
        for (i = m_vecRecords.size(); i > 0; --i)
        {
            m_vecRecords[i - 1].vecRemoved.clear();
            m_vecRecords.pop_back();
        }
        if (m_iStepPos > 0)
        {
            for (i = 0; i < 361; ++i)
            {
                m_lpGameBoard[i].stone_color = CGameBase::SC_NULL;
            }
            m_iStepPos = 0;
        }
    }
    m_scTurnColor = CGameBase::SC_BLACK;
    m_bAlive = true;
}

void CGameManager::OnClearAnalyze()
{
    int i;
    CGameBase::BoardPoint *lpbpCurrent;
    lpbpCurrent = m_lpGameBoard;
    for (i = 0; i < 361; ++i)
    {
        lpbpCurrent->pv.clear();
        lpbpCurrent->visits = 0;
        lpbpCurrent->order = -1;
        lpbpCurrent->win_rate = -1;
        ++lpbpCurrent;
    }
}

void CGameManager::OnReadSgf(std::ifstream &ifs)
{
    char c;
    int x, y;
    CGameBase::StoneColor stone_color;
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
                    stone_color = CGameBase::SC_BLACK;
                }
                else if (c == 'W')
                {
                    stone_color = CGameBase::SC_WHITE;
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
