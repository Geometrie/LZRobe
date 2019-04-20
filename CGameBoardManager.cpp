#include "CGameBoardManager.h"
CGameBoardManager::CGameBoardManager()
{
	m_scTurnColor = SC_BLACK;
	m_bAlive = true;
	m_bAcceptAnalyze = true;
	m_lpiPrisoners[0] = m_lpiPrisoners[1] = 0;
	m_lpAnalyzingEnd = m_lpAnalyzingStones;
	m_lpemCurrentMove = &m_emBlankMove;
	m_nHandicap = 0;
	m_iHandicapPutting = 0;
}


CGameBoardManager::~CGameBoardManager()
{
	OnClearGameRecord();
}

void CGameBoardManager::OnAddHandicap(int x, int y)
{
	CGameBase::BoardPoint *lpbpPoint;
	if (x >= 0 && x < nBoardSize && y >= 0 && y < nBoardSize && m_iHandicapPutting < m_nHandicap)
	{
		lpbpPoint = m_fnPoint(x, y);
		m_lplpbpHandicap[m_iHandicapPutting] = lpbpPoint;
		++m_iHandicapPutting;
		lpbpPoint->stone_color = SC_BLACK;
	}
}

void CGameBoardManager::OnSetHandicap()
{
	char *lplpcHandicap[] = { "pddp", "pddpdd", "pddpddpp", "pddpddppjj", "pddpddppdjpj", "pddpddppdjpjjj", "pddpddppdjpjjdjp", "pddpddppdjpjjdjpjj" };
	char *lpcCoordinate = lplpcHandicap[m_nHandicap - 2];
	int x, y, i;
	if (m_nHandicap > 1 && m_nHandicap <= 9)
	{
		for (i = 0; i < m_nHandicap; ++i)
		{
			x = int(lpcCoordinate[i * 2] - 'a');
			y = int(lpcCoordinate[i * 2 + 1] - 'a');
			OnAddHandicap(x, y);
		}
	}
	m_scTurnColor = SC_WHITE;
}


bool CGameBoardManager::OnTestMove(int x, int y)
{
	bool bLegal;
	CGameBase::BoardPoint *lpbpKoMarkBackUp;
	lpbpKoMarkBackUp = m_lpbpKoMark;
	bLegal = m_fnIsLegalMove(m_scTurnColor, m_fnPoint(x, y));
	m_lpbpKoMark = lpbpKoMarkBackUp;
	m_lprmRemoveEnd = m_lprmRemove;
	return bLegal;
}

void CGameBoardManager::m_fnSwapShorter(CGameBase::ExtendMove *lpemKnot)
{
	CGameBase::ExtendMove *lpemNext;
	lpemNext = lpemKnot->shorter;
	if (lpemNext->shorter != NULL)
	{
		lpemNext->shorter->longer = lpemKnot;
	}
	if (lpemKnot->longer != NULL)
	{
		lpemKnot->longer->shorter = lpemNext;
	}
	lpemKnot->shorter = lpemNext->shorter;
	lpemNext->longer = lpemKnot->longer;
	lpemKnot->longer = lpemNext;
	lpemNext->shorter = lpemKnot;
}

void CGameBoardManager::m_fnSwapLonger(CGameBase::ExtendMove *lpemKnot)
{
	CGameBase::ExtendMove *lpemPrev;
	lpemPrev = lpemKnot->longer;
	if (lpemPrev->longer != NULL)
	{
		lpemPrev->longer->shorter = lpemKnot;
	}
	if (lpemKnot->shorter != NULL)
	{
		lpemKnot->shorter->longer = lpemPrev;
	}
	lpemKnot->longer = lpemPrev->longer;
	lpemPrev->shorter = lpemKnot->shorter;
	lpemKnot->shorter = lpemPrev;
	lpemPrev->longer = lpemKnot;

}

bool CGameBoardManager::OnAddMove(int x, int y)
{
	bool bLegal;
	CGameBase::BoardPoint *lpbpPoint, *lpbpKoMarkBackUp;
	CGameBase::Remove *lprmRemoveVisitor;
	CGameBase::ExtendMove *lpemLastMove, emNewMove, *lpemMoveVisitor, *lpemBranchVisitor;
	int iBranchDepth;
	if (x == nBoardSize)
	{
		if (y == 1)
		{
			m_bAlive = false;
		}
		else if (y == 0)
		{
			if (m_lpemCurrentMove->x == nBoardSize && m_lpemCurrentMove->y == 0)
			{
				m_bAlive = false;
			}
		}
		bLegal = true;
	}
	if (m_bAlive)
	{
		lpemBranchVisitor = m_lpemCurrentMove->search(x, y);
		if (lpemBranchVisitor != NULL)
		{
			OnRedoMove(lpemBranchVisitor);
			bLegal = true;
		}
		else
		{
			lpbpPoint = m_fnPoint(x, y);
			lpbpKoMarkBackUp = m_lpbpKoMark;
			bLegal = m_fnIsLegalMove(m_scTurnColor, lpbpPoint);
			if (bLegal)
			{
				lpbpPoint->stone_color = m_scTurnColor;
				emNewMove.stone_color = m_scTurnColor;
				emNewMove.x = x;
				emNewMove.y = y;
				m_scTurnColor = opposite_color(m_scTurnColor);
				if (m_lprmRemove != m_lprmRemoveEnd)
				{
					for (lprmRemoveVisitor = m_lprmRemove; lprmRemoveVisitor != m_lprmRemoveEnd; ++lprmRemoveVisitor)
					{
						lprmRemoveVisitor->bp->stone_color = SC_NULL;
					}
					emNewMove.remove_len = int(m_lprmRemoveEnd - m_lprmRemove);
					emNewMove.remove_data = m_rmplRemoved.m_fnWriteData(m_lprmRemove, emNewMove.remove_len);
					if (emNewMove.remove_data == NULL)
					{
						bLegal = false;
					}
					if (emNewMove.remove_len > 0)
					{
						switch (lpbpPoint->stone_color)
						{
						case SC_BLACK:
							m_lpiPrisoners[0] += emNewMove.remove_len;
							break;
						case SC_WHITE:
							m_lpiPrisoners[1] += emNewMove.remove_len;
							break;
						}
					}
				}
				if (bLegal)
				{
					m_lprmRemoveEnd = m_lprmRemove;
					lpemLastMove = m_lpemCurrentMove;
					m_lpemCurrentMove = m_emplGameRecords.m_fnWriteData(&emNewMove, 1);
					if (m_lpemCurrentMove == NULL)
					{
						m_lpbpKoMark = lpbpKoMarkBackUp;
						if (emNewMove.remove_len > 0)
						{
							m_rmplRemoved.m_fnDropData(emNewMove.remove_data, emNewMove.remove_len);
						}
					}
					else
					{
						m_lpemCurrentMove->parent = lpemLastMove;
						m_lpemCurrentMove->step = lpemLastMove->step + 1;
						if (lpemLastMove->child == NULL)
						{
							lpemLastMove->child = m_lpemCurrentMove;
						}
						else
						{
							lpemBranchVisitor = lpemLastMove->child;
							while (lpemBranchVisitor->shorter != NULL)
							{
								lpemBranchVisitor = lpemBranchVisitor->shorter;
							}
							lpemBranchVisitor->shorter = m_lpemCurrentMove;
							m_lpemCurrentMove->longer = lpemBranchVisitor;
						}
						++(lpemLastMove->branch);
						lpemMoveVisitor = m_lpemCurrentMove;
						while (lpemMoveVisitor->parent != NULL)
						{
							while (lpemMoveVisitor->longer != NULL && lpemMoveVisitor->longer->depth < lpemMoveVisitor->depth)
							{
								m_fnSwapLonger(lpemMoveVisitor);
							}
							while (lpemMoveVisitor->parent->child->longer != NULL)
							{
								lpemMoveVisitor->parent->child = lpemMoveVisitor->parent->child->longer;
							}
							iBranchDepth = lpemMoveVisitor->depth + 1;
							if (iBranchDepth > lpemMoveVisitor->parent->depth)
							{
								lpemMoveVisitor->parent->depth = iBranchDepth;
								lpemMoveVisitor = lpemMoveVisitor->parent;
							}
							else
							{
								lpemMoveVisitor = &m_emBlankMove;
							}
						}
					}
				}
				else
				{
					m_lpbpKoMark = lpbpKoMarkBackUp;
				}
			}
			else
			{
				m_lpbpKoMark = lpbpKoMarkBackUp;
			}
		}
	}
	return bLegal;
}
bool CGameBoardManager::OnBackMove()
{
	CGameBase::Remove *m_lprmRemoveVisitor, *m_lprmRemoveEnd;
	CGameBase::BoardPoint *lpbp;
	StoneColor scRemovedColor;
	bool bSucceed;
	if (m_lpemCurrentMove != &m_emBlankMove)
	{
		scRemovedColor = opposite_color(m_lpemCurrentMove->stone_color);
		lpbp = m_fnPoint(m_lpemCurrentMove->x, m_lpemCurrentMove->y);
		lpbp->stone_color = SC_NULL;
		if (m_lpemCurrentMove->remove_len > 0)
		{
			m_lprmRemoveEnd = m_lpemCurrentMove->remove_data + m_lpemCurrentMove->remove_len;
			for (m_lprmRemoveVisitor = m_lpemCurrentMove->remove_data; m_lprmRemoveVisitor != m_lprmRemoveEnd; ++m_lprmRemoveVisitor)
			{
				m_lprmRemoveVisitor->bp->stone_color = scRemovedColor;
			}
			switch (m_lpemCurrentMove->stone_color)
			{
			case SC_BLACK:
				m_lpiPrisoners[0] -= m_lpemCurrentMove->remove_len;
				break;
			case SC_WHITE:
				m_lpiPrisoners[1] -= m_lpemCurrentMove->remove_len;
				break;
			}
		}
		m_scTurnColor = m_lpemCurrentMove->stone_color;
		m_lpemCurrentMove = m_lpemCurrentMove->parent;
		bSucceed = true;
	}
	else
	{
		bSucceed = false;
	}
	return bSucceed;
}

bool CGameBoardManager::OnRedoMove(CGameBase::ExtendMove *lpemMove)
{
	CGameBase::Remove *m_lprmRemoveVisitor, *m_lprmRemoveEnd;
	CGameBase::BoardPoint *lpbp;
	bool bSucceed;
	if (lpemMove == NULL)
	{
		lpemMove = m_lpemCurrentMove->child;
	}
	if (lpemMove != NULL)
	{
		m_lpemCurrentMove = lpemMove;
		lpbp = m_fnPoint(m_lpemCurrentMove->x, m_lpemCurrentMove->y);
		lpbp->stone_color = m_lpemCurrentMove->stone_color;
		if (m_lpemCurrentMove->remove_len > 0)
		{
			m_lprmRemoveEnd = m_lpemCurrentMove->remove_data + m_lpemCurrentMove->remove_len;
			for (m_lprmRemoveVisitor = m_lpemCurrentMove->remove_data; m_lprmRemoveVisitor != m_lprmRemoveEnd; ++m_lprmRemoveVisitor)
			{
				m_lprmRemoveVisitor->bp->stone_color = SC_NULL;
			}
			switch (m_lpemCurrentMove->stone_color)
			{
			case SC_BLACK:
				m_lpiPrisoners[0] += m_lpemCurrentMove->remove_len;
				break;
			case SC_WHITE:
				m_lpiPrisoners[1] += m_lpemCurrentMove->remove_len;
				break;
			}
		}
		m_scTurnColor = opposite_color(m_lpemCurrentMove->stone_color);
		bSucceed = true;
	}
	else
	{
		bSucceed = false;
	}
	return bSucceed;
}

void CGameBoardManager::OnDeleteBranch(CGameBase::ExtendMove *lpemBranch)
{
	std::queue<CGameBase::ExtendMove*> qulpemQueue;
	std::stack<CGameBase::ExtendMove*> stklpemStack;
	CGameBase::ExtendMove *lpemMoveVisitor, *lpemBranchVisitor;
	lpemBranch->depth = -1;
	lpemMoveVisitor = lpemBranch;
	while (lpemMoveVisitor->parent != NULL)
	{
		while (lpemMoveVisitor->shorter != NULL && lpemMoveVisitor->depth < lpemMoveVisitor->shorter->depth)
		{
			m_fnSwapShorter(lpemMoveVisitor);
		}
		while (lpemMoveVisitor->parent->child->longer != NULL)
		{
			lpemMoveVisitor->parent->child = lpemMoveVisitor->parent->child->longer;
		}
		if (lpemMoveVisitor->parent->depth > lpemMoveVisitor->parent->child->depth + 1)
		{
			lpemMoveVisitor->parent->depth = lpemMoveVisitor->parent->child->depth + 1;
			lpemMoveVisitor = lpemMoveVisitor->parent;
		}
		else
		{
			lpemMoveVisitor = &(m_emBlankMove);
		}
	}
	if (lpemBranch->longer != NULL)
	{
		lpemBranch->longer->shorter = NULL;
	}
	if (lpemBranch->parent != NULL)
	{
		--(lpemBranch->parent->branch);
		if (lpemBranch->parent->child == lpemBranch)
		{
			lpemBranch->parent->child = NULL;
		}
	}
	qulpemQueue.push(lpemBranch);
	while (!qulpemQueue.empty())
	{
		lpemMoveVisitor = qulpemQueue.front();
		qulpemQueue.pop();
		if (lpemMoveVisitor->child != NULL)
		{
			lpemBranchVisitor = lpemMoveVisitor->child;
			while (lpemBranchVisitor != NULL)
			{
				qulpemQueue.push(lpemBranchVisitor);
				lpemBranchVisitor = lpemBranchVisitor->shorter;
			}
		}
		stklpemStack.push(lpemMoveVisitor);
	}
	while (!stklpemStack.empty())
	{
		lpemMoveVisitor = stklpemStack.top();
		stklpemStack.pop();
		if (lpemMoveVisitor->remove_data != NULL)
		{
			m_rmplRemoved.m_fnDropData(lpemMoveVisitor->remove_data, lpemMoveVisitor->remove_len);
			m_emplGameRecords.m_fnDropData(lpemMoveVisitor, 1);
		}
	}
}


void CGameBoardManager::OnClearGameRecord()
{
	CGameBase::BoardPoint *lpbpBoardVisitor;
	lpbpBoardVisitor = m_lpbpGameBoard + nBoardSize * nBoardSize + 2;
	while (lpbpBoardVisitor != m_lpbpGameBoard)
	{
		--lpbpBoardVisitor;
		lpbpBoardVisitor->stone_color = SC_NULL;
	}
	m_rmplRemoved.m_fnClear();
	m_emplGameRecords.m_fnClear();
	m_emBlankMove.release();
	m_lpemCurrentMove = &(m_emBlankMove);
	m_scTurnColor = SC_BLACK;
	m_bAlive = true;
	m_bAcceptAnalyze = true;
	m_lpiPrisoners[0] = m_lpiPrisoners[1] = 0;
	m_lpAnalyzingEnd = m_lpAnalyzingStones;
	m_lpemCurrentMove = &m_emBlankMove;
	m_nHandicap = 0;
	m_iHandicapPutting = 0;
}

void CGameBoardManager::OnClearAnalyze()
{
	CGameBase::BoardPoint *lpbpCurrent;
	CGameBase::BoardPoint **lplpbpAnalyzing;
	for (lplpbpAnalyzing = m_lpAnalyzingStones; lplpbpAnalyzing != m_lpAnalyzingEnd; ++lplpbpAnalyzing)
	{
		lpbpCurrent = *lplpbpAnalyzing;
		lpbpCurrent->pv_len = 0;
		lpbpCurrent->visits = 0;
		lpbpCurrent->order = -1;
		lpbpCurrent->win_rate = -1;
	}
	m_lpAnalyzingEnd = m_lpAnalyzingStones;
}

