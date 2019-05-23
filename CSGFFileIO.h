#ifndef CSGFFILEIO_H
#define CSGFFILEIO_H
#include <stdlib.h>
#include <fstream>
#include "CGameBoardManager.h"
class CSGFFileIO: public CGameBoardManager
{
public:
	void OnReadSGF(std::ifstream &ifs);
	void OnWriteSGF(std::ofstream &ofs);
protected:
	enum COMMAND_TYPE
	{
		CT_NULL,
		CT_KOMI,
		CT_SIZE,
		CT_HANDICAP,
		CT_RESULT,
		CT_ADD_BLACK,
		CT_BLACK_MOVE,
		CT_WHITE_MOVE,
		CT_NAME,
		CT_COMMENT
	};
	enum DATA_TYPE
	{
		DT_COORDINATE,
		DT_NUMBER,
		DT_STRING,
	};
	bool m_fnApplyData(char *lpstrData, COMMAND_TYPE ctCommand);
	COMMAND_TYPE m_fnClassifyCommand(char *lpstrCommand);
	DATA_TYPE m_fnClassifyData(char *lpstrData);
	void m_fnConvertCoord(char *lpstrData, int &x, int &y);
};
#endif