#ifndef CGORULEKEEPER_H
#define CGORULEKEEPER_H
#include "CGameBase.h"
class CGoRuleKeeper
{
public:
	std::vector<CGameBase::ExtendMove> m_vecRecords;
	CGameBase::BoardPoint m_lpGameBoard[363];
	StoneColor m_scTurnColor;
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
		return m_lpGameBoard + (x * 19 + y);
	}
	void m_fnSelectStoneBlock(int x, int y, std::vector<CGameBase::BasePosition> &vecBlock);
	int m_fnCountLiberty(std::vector<CGameBase::BasePosition> &vecBlock);
	bool m_fnIsLegalMove(StoneColor sc, int x, int y, std::vector<CGameBase::BoardPoint*> &vecRemove);
};
#endif