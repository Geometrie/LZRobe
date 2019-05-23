#ifndef CGORULEKEEPER_H
#define CGORULEKEEPER_H
#include <queue>
#include "CPool.h"
class CGoRuleKeeper
{
public:
	CGoRuleKeeper();
	~CGoRuleKeeper();
	CPool<CGameBase::ExtendMove> m_emplGameRecords;
	CPool<CGameBase::Remove> m_rmplRemoved;
	CGameBase::BoardPoint *m_lpbpGameBoard;
	CGameBase::Remove *m_lprmRemove, *m_lprmRemoveEnd;
	CGameBase::BoardPoint *m_lpbpKoMark;
	StoneColor m_scTurnColor;
	bool m_bTerritoryMarked;
	static StoneColor opposite_color(StoneColor original_color)
	{
		StoneColor image_color;
		image_color = SC_NULL;
		switch (original_color)
		{
		case SC_NULL:
			image_color = SC_NULL;
			break;
		case SC_BLACK:
			image_color = SC_WHITE;
			break;
		case SC_WHITE:
			image_color = SC_BLACK;
			break;
		}
		return image_color;
	};
	CGameBase::BoardPoint* m_fnPoint(int x, int y)
	{
		return m_lpbpGameBoard + (x * nBoardSize + y);
	}
	void m_fnCoordinate(CGameBase::BoardPoint *lpbp, int &x, int &y)
	{
		int iInd;
		iInd = int(lpbp - m_lpbpGameBoard);
		x = iInd / nBoardSize;
		y = iInd % nBoardSize;
	}
	void m_fnChangeSize();
	void m_fnSelectStoneBlock(CGameBase::BoardPoint *lpbpSeed);
	int m_fnCountLiberty();
	bool m_fnIsLegalMove(StoneColor sc, CGameBase::BoardPoint *lpbpPosition);
	void m_fnMarkTerritory();
	int m_fnTerritoryComp();
	void m_fnClearTerritoryMark();
private:
	CGameBase::BoardPoint **m_lplpbpSelectStones, **m_lplpbpSelectEnd;
	CGameBase::BoardPoint **m_lplpbpCountLiberties, **m_lplpbpCountEnd;
	CGameBase::BoardPoint **m_lplpbpNeighbour, **m_lplpbpNeighbourEnd;
};
#endif