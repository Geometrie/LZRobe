#ifndef CGAMEMANAGER_H
#define CGAMEMANAGER_H
#include <fstream>
#include <queue>
#include "CGameBase.h"
class CGameManager
{
public:
    CGameManager();
    ~CGameManager();
    std::vector<CGameBase::ExtendMove> m_vecRecords;
    int m_iStepPos;
    bool m_bAlive, m_bAcceptAnalyze;
    CGameBase::BoardPoint m_lpGameBoard[361];
    CGameBase::StoneColor m_scTurnColor;
    bool OnTestMove(int x, int y);
    bool OnAddMove(int x, int y);
    bool OnBackMove();
    bool OnRedoMove();
    bool OnModifyGameRecord();
    void OnClearGameRecord();
    void OnClearAnalyze();
    CGameBase::BoardPoint* m_fnPoint(int x, int y)
    {
        return m_lpGameBoard + (x * 19 + y);
    }
    void OnReadSgf(std::ifstream &ifs);
protected:
    CGameBase::StoneColor opposite_color(CGameBase::StoneColor original_color)
    {
        CGameBase::StoneColor image_color;
        image_color = CGameBase::SC_NULL;
        switch (original_color)
        {
        case CGameBase::SC_NULL:
            image_color = CGameBase::SC_NULL;
            break;
        case CGameBase::SC_BLACK:
            image_color = CGameBase::SC_WHITE;
            break;
        case CGameBase::SC_WHITE:
            image_color = CGameBase::SC_BLACK;
            break;
        }
        return image_color;
    };
    void m_fnSelectStoneBlock(int x, int y, std::vector<CGameBase::BasePosition> &vecBlock);
    int m_fnCountLiberty(std::vector<CGameBase::BasePosition> &vecBlock);
    bool m_fnIsLegalMove(CGameBase::StoneColor sc, int x, int y, std::vector<CGameBase::BoardPoint*> &vecRemove);
};
#endif // CGAMEMANAGER_H
