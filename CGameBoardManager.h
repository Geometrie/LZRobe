#ifndef CGAMEMANAGER_H
#define CGAMEMANAGER_H
#include <fstream>
#include <list>
#include "CGoRuleKeeper.h"
class CGameBoardManager: public CGoRuleKeeper
{
public:
    CGameBoardManager();
    ~CGameBoardManager();
	std::list<CGameBase::BoardPoint*> m_lstExistingStones;
	std::vector<CGameBase::BoardPoint*> m_vecAnalyzingStones;
    int m_iStepPos, m_lpiPrisoners[2];
    bool m_bAlive, m_bAcceptAnalyze;
	void m_fnRefreshStones();
    bool OnTestMove(int x, int y);
    bool OnAddMove(int x, int y);
    bool OnBackMove();
    bool OnRedoMove();
    bool OnModifyGameRecord();
    void OnClearGameRecord();
	void OnClearAnalyze();
    void OnReadSgf(std::ifstream &ifs);
protected:
};
#endif // CGAMEMANAGER_H
