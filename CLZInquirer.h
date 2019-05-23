#ifndef CLZINQUIRER_H
#define CLZINQUIRER_H
#include <wx/string.h>
#include <wx/stream.h>
#include <wx/thread.h>
#include "CGameStatusManager.h"
enum INQUIRE_TYPE
{
	IT_NULL,
	IT_NAME,
	IT_TIME_SETTINGS,
	IT_CHANGE_BOARD_SIZE,
	IT_HANDICAP,
	IT_CLEAR_BOARD,
	IT_PLAY,
	IT_GEN_MOVE,
	IT_BACKWARD,
//	IT_RESULT,
	IT_ANALYZE,
	IT_INTERRUPT,
	IT_QUIT
};

struct InquireInfo
{
	INQUIRE_TYPE itInquireType;
	union
	{
		struct
		{
			StoneColor scColor;
			int x, y;
		};
		struct
		{
			int iHandicapStones;
		};
		struct
		{
			int iGlobalTime, iStepTime, iSteps;
		};
		struct
		{
			int iBoardSize;
		};
	};
};

class CLZInquirer
{
public:
	CGameStatusManager *m_lpGameStatusManager;
	wxOutputStream *m_lpOutputStream;
	int m_iThinkingTime, m_iAnalyzeInterval;
	CSGFFileIO m_GameBoardManager;
	std::queue<InquireInfo> m_quiiLZInquireQueue;
	bool m_bOccupied;
	wxMutex m_OccupyMutex;
	CLZInquirer();
	~CLZInquirer()
	{
		delete m_lpGameStatusManager;
	}
	void m_fnLZApplyInquire(InquireInfo *lpiiInquireInfo);
	void m_fnReleaseInquire();
	void m_fnLZExecuteFirstInquire();
	void m_fnLZInquireName();
	void m_fnLZSetThinkingTime();
	void m_fnLZChangeBoardSize(int iBoardSize);
	void m_fnLZClearBoard();
	void m_fnLZSetHandicap();
	void m_fnLZAppendMove(StoneColor scColor, int x, int y);
	void m_fnLZInquireMove(StoneColor scColor);
	//void m_fnLZInquireResult();
	void m_fnLZInquireAnalyze();
	void m_fnLZReloadGameRecord();
	void m_fnLZJumpTo(int iNewStep);
	void m_fnLZForward(CGameBase::ExtendMove *lpemMove = NULL);
	void m_fnLZBackward();
};
#endif