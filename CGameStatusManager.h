#ifndef CGAMESTATUSMANAGER_H
#define CGAMESTATUSMANAGER_H
#include "CGameBoardManager.h"
#include <wx/toolbar.h>
#include <wx/menu.h>
enum
{
	ID_SELECT_ENGINE = 1000,
	ID_SELECT_WEIGHT,
	ID_LEELA_ZERO,
	ID_BLACK_DOG,
	ID_WHITE_DOG,
	ID_ANALYZE,
	ID_SHOW_STEP,
	ID_FINAL_SCORE
};

enum EngineStatus
{
	ES_CLOSED,
	ES_WAITING_OPEN,
	ES_WAITING_CLOSE,
	ES_OPENED,
};


class CGameStatusManager
{
public:
	CGameStatusManager();
	EngineStatus m_esCurrentEngine;
	wxToolBar *m_lpToolBar;
	wxMenu *m_lpEditMenu;
	void m_fnTryToOpenEngine();
	void m_fnEngineConfirmed();
	void m_fnTryToCloseEngine();
	void m_fnEngineClosed();
	void m_fnSetBlackDog();
	void m_fnSetWhiteDog();
	void m_fnSetAnalyze();
	bool m_fnInquireAI(StoneColor scColor)
	{
		return (m_esCurrentEngine == ES_OPENED && (((scColor == SC_BLACK) && m_lpToolBar->GetToolState(ID_BLACK_DOG)) || ((scColor == SC_WHITE) && m_lpToolBar->GetToolState(ID_WHITE_DOG))));
	}
	bool m_fnUserAuthorized(StoneColor scColor)
	{
		return (((scColor == SC_BLACK) && !m_lpToolBar->GetToolState(ID_BLACK_DOG)) || ((scColor == SC_WHITE) && !m_lpToolBar->GetToolState(ID_WHITE_DOG)));
	}
	bool m_fnAnalyzing()
	{
		return m_lpToolBar->GetToolState(ID_ANALYZE);
	}
	bool m_fnBothAuthorized()
	{
		return (!(m_lpToolBar->GetToolState(ID_BLACK_DOG) || m_lpToolBar->GetToolState(ID_WHITE_DOG)));
	}
};
#endif