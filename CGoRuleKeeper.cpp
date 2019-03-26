#include <queue>
#include "CGoRuleKeeper.h"
void CGoRuleKeeper::m_fnSelectStoneBlock(int x, int y, std::vector<CGameBase::BasePosition> &vecBlock)
{
	StoneColor stone_color;
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


int CGoRuleKeeper::m_fnCountLiberty(std::vector<CGameBase::BasePosition> &vecBlock)
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
				if (lpbpTest->stone_color == SC_NULL && (lpbpTest->mark & 1) == 0)
				{
					lpbpTest->mark += 1;
					vecLiberties.push_back(lpbpTest);
				}
			}
		}
	}
	nCount = int(vecLiberties.size());
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

bool CGoRuleKeeper::m_fnIsLegalMove(StoneColor stone_color, int x, int y, std::vector<CGameBase::BoardPoint*> &vecRemove)
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
			if (lpbpTest->stone_color == SC_NULL)
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