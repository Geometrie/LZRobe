#include "CGoRuleKeeper.h"
CGoRuleKeeper::CGoRuleKeeper()
{
	m_lpbpGameBoard = new CGameBase::BoardPoint[nBoardSize * nBoardSize + 1];
	m_lplpbpSelectStones = new CGameBase::BoardPoint*[nBoardSize * nBoardSize - 1];
	m_lplpbpSelectEnd = m_lplpbpSelectStones;
	m_lplpbpCountLiberties = new CGameBase::BoardPoint*[nBoardSize * nBoardSize - 1];
	m_lplpbpCountEnd = m_lplpbpCountLiberties;
	m_lprmRemove = new CGameBase::Remove[nBoardSize * nBoardSize - 1];
	m_lprmRemoveEnd = m_lprmRemove;
	m_lplpbpNeighbour = new CGameBase::BoardPoint*[nBoardSize * nBoardSize - 1];
	m_lplpbpNeighbourEnd = m_lplpbpNeighbour;
	m_lpbpKoMark = NULL;
	m_emplGameRecords.init(nBoardSize * nBoardSize * 4);
	m_rmplRemoved.init(nBoardSize * nBoardSize * 4);
}
CGoRuleKeeper::~CGoRuleKeeper()
{
	m_rmplRemoved.release();
	m_emplGameRecords.release();
	delete[]m_lplpbpNeighbour;
	delete[]m_lprmRemove;
	delete[]m_lplpbpCountLiberties;
	delete[]m_lplpbpSelectStones;
	delete[]m_lpbpGameBoard;
}

void CGoRuleKeeper::m_fnChangeSize()
{
	m_rmplRemoved.release();
	m_emplGameRecords.release();
	delete[]m_lplpbpNeighbour;
	delete[]m_lprmRemove;
	delete[]m_lplpbpCountLiberties;
	delete[]m_lplpbpSelectStones;
	delete[]m_lpbpGameBoard;
	m_lpbpGameBoard = new CGameBase::BoardPoint[nBoardSize * nBoardSize + 1];
	m_lplpbpSelectStones = new CGameBase::BoardPoint*[nBoardSize * nBoardSize - 1];
	m_lplpbpSelectEnd = m_lplpbpSelectStones;
	m_lplpbpCountLiberties = new CGameBase::BoardPoint*[nBoardSize * nBoardSize - 1];
	m_lplpbpCountEnd = m_lplpbpCountLiberties;
	m_lprmRemove = new CGameBase::Remove[nBoardSize * nBoardSize - 1];
	m_lprmRemoveEnd = m_lprmRemove;
	m_lplpbpNeighbour = new CGameBase::BoardPoint*[nBoardSize * nBoardSize - 1];
	m_lplpbpNeighbourEnd = m_lplpbpNeighbour;
	m_lpbpKoMark = NULL;
	m_emplGameRecords.init(nBoardSize * nBoardSize * 4);
	m_rmplRemoved.init(nBoardSize * nBoardSize * 4);
}

void CGoRuleKeeper::m_fnSelectStoneBlock(CGameBase::BoardPoint *lpbpSeed)
{
	std::queue<CGameBase::BoardPoint*> qubpQueue;
	CGameBase::BoardPoint *lpbpTest, **lplpbpVisitor;
	int i, xSeed, ySeed, xTest, yTest;;
	qubpQueue.push(lpbpSeed);
	lpbpSeed->mark += 1;
	*m_lplpbpSelectEnd = lpbpSeed;
	++m_lplpbpSelectEnd;
	while (qubpQueue.size() > 0)
	{
		lpbpSeed = qubpQueue.front();
		qubpQueue.pop();
		m_fnCoordinate(lpbpSeed, xSeed, ySeed);
		for (i = 0; i < 4; ++i)
		{
			xTest = xSeed + (1 - i % 2) * (1 - (i / 2) * 2);
			yTest = ySeed + (i % 2) * (1 - (i / 2) * 2);
			if (xTest >= 0 && xTest < nBoardSize && yTest >= 0 && yTest < nBoardSize)
			{
				lpbpTest = m_fnPoint(xTest, yTest);
				if ((lpbpTest->stone_color == lpbpSeed->stone_color) && ((lpbpTest->mark & 1) == 0))
				{
					lpbpTest->mark += 1;
					*m_lplpbpSelectEnd = lpbpTest;
					++m_lplpbpSelectEnd;
					qubpQueue.push(lpbpTest);
				}
			}
		}
	}
	for (lplpbpVisitor = m_lplpbpSelectStones; lplpbpVisitor != m_lplpbpSelectEnd; ++lplpbpVisitor)
	{
		(*lplpbpVisitor)->mark -= 1;
	}
}


int CGoRuleKeeper::m_fnCountLiberty()
{
	CGameBase::BoardPoint **lplpbpVisitor;
	CGameBase::BoardPoint *lpbpTest;
	int i, xStone, yStone, xTest, yTest, nCount;
	for (lplpbpVisitor = m_lplpbpSelectStones; lplpbpVisitor != m_lplpbpSelectEnd; ++lplpbpVisitor)
	{
		m_fnCoordinate(*lplpbpVisitor, xStone, yStone);
		for (i = 0; i < 4; ++i)
		{
			xTest = xStone + (1 - i % 2) * (1 - (i / 2) * 2);
			yTest = yStone + (i % 2) * (1 - (i / 2) * 2);
			if (xTest >= 0 && xTest < nBoardSize && yTest >= 0 && yTest < nBoardSize)
			{
				lpbpTest = m_fnPoint(xTest, yTest);
				if (lpbpTest->stone_color == SC_NULL && (lpbpTest->mark & 1) == 0)
				{
					lpbpTest->mark += 1;
					*m_lplpbpCountEnd = lpbpTest;
					++m_lplpbpCountEnd;
				}
			}
		}
	}
	for (lplpbpVisitor = m_lplpbpCountLiberties; lplpbpVisitor != m_lplpbpCountEnd; ++lplpbpVisitor)
	{
		(*lplpbpVisitor)->mark -= 1;
	}
	nCount = int(m_lplpbpCountEnd - m_lplpbpCountLiberties);
	m_lplpbpCountEnd = m_lplpbpCountLiberties;
	return nCount;
}

bool CGoRuleKeeper::m_fnIsLegalMove(StoneColor sc, CGameBase::BoardPoint *lpbpPosition)
{
	int i, xCenter, yCenter, xNeighbour, yNeighbour, nLiberty;
	bool bLegal;
	CGameBase::BoardPoint *lpbpNeighbour, **lplpbpBlockVisitor;
	m_fnCoordinate(lpbpPosition, xCenter, yCenter);
	if (xCenter == nBoardSize && (yCenter == 0 || yCenter == 1))
	{
		bLegal = true;
	}
	else if (lpbpPosition->stone_color != SC_NULL)
	{
		bLegal = false;
	}
	else
	{
		bLegal = false;
		for (i = 0; i < 4; ++i)
		{
			xNeighbour = xCenter + (1 - i % 2) * (1 - (i / 2) * 2);
			yNeighbour = yCenter + (i % 2) * (1 - (i / 2) * 2);
			if (xNeighbour >= 0 && xNeighbour < nBoardSize && yNeighbour >= 0 && yNeighbour < nBoardSize)
			{
				lpbpNeighbour = m_fnPoint(xNeighbour, yNeighbour);
				if (lpbpNeighbour->stone_color == SC_NULL)
				{
					bLegal = true;
				}
				else if ((lpbpNeighbour->mark & 2) == 0)
				{
					m_fnSelectStoneBlock(lpbpNeighbour);
					nLiberty = m_fnCountLiberty();
					for (lplpbpBlockVisitor = m_lplpbpSelectStones; lplpbpBlockVisitor != m_lplpbpSelectEnd; ++lplpbpBlockVisitor)
					{
						(*lplpbpBlockVisitor)->mark += 2;
						*m_lplpbpNeighbourEnd = *lplpbpBlockVisitor;
						++m_lplpbpNeighbourEnd;
					}
					if (lpbpNeighbour->stone_color == sc)
					{
						if (nLiberty > 1)
						{
							bLegal = true;
						}
					}
					else if (nLiberty == 1)
					{
						for (lplpbpBlockVisitor = m_lplpbpSelectStones; lplpbpBlockVisitor != m_lplpbpSelectEnd; ++lplpbpBlockVisitor)
						{
							m_lprmRemoveEnd->bp = *lplpbpBlockVisitor;
							++m_lprmRemoveEnd;
						}
						bLegal = true;
					}
					m_lplpbpSelectEnd = m_lplpbpSelectStones;
				}
			}
		}
		if (m_lplpbpNeighbourEnd != m_lplpbpNeighbour)
		{
			for (lplpbpBlockVisitor = m_lplpbpNeighbour; lplpbpBlockVisitor != m_lplpbpNeighbourEnd; ++lplpbpBlockVisitor)
			{
				(*lplpbpBlockVisitor)->mark -= 2;
			}
			m_lplpbpNeighbourEnd = m_lplpbpNeighbour;
		}
	}
	if (m_lprmRemoveEnd - m_lprmRemove == 1)
	{
		if (lpbpPosition == m_lpbpKoMark)
		{
			bLegal = false;
			m_lprmRemoveEnd = m_lprmRemove;
		}
		else
		{
			m_lpbpKoMark = m_lprmRemove->bp;
		}
	}
	else
	{
		m_lpbpKoMark = NULL;
	}
	return bLegal;
}