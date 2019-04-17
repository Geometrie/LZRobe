#ifndef CGAMEMANAGER_H
#define CGAMEMANAGER_H
#include <stack>
#include "CGoRuleKeeper.h"
class CGameBoardManager: public CGoRuleKeeper
{
public:
    CGameBoardManager();
    ~CGameBoardManager();
	CGameBase::BoardPoint *m_lpAnalyzingStones[64], **m_lpAnalyzingEnd;
	CGameBase::BoardPoint* m_lplpbpHandicap[9];
	int m_nHandicap, m_iHandicapPutting;
	CGameBase::ExtendMove *m_lpemCurrentMove, m_emBlankMove;
    int m_lpiPrisoners[2];
    bool m_bAlive, m_bAcceptAnalyze;
	void OnAddHandicap(int x, int y);
	void OnSetHandicap();
    bool OnTestMove(int x, int y);
    bool OnAddMove(int x, int y);
    bool OnBackMove();
    bool OnRedoMove(CGameBase::ExtendMove *lpemMove = NULL);
    void OnDeleteBranch(CGameBase::ExtendMove *lpemBranch);
    void OnClearGameRecord();
	void OnClearAnalyze();
protected:
	void m_fnSwapShorter(CGameBase::ExtendMove *lpemKnot);
	void m_fnSwapLonger(CGameBase::ExtendMove *lpemKnot);
};
#endif // CGAMEMANAGER_H
