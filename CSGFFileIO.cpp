#include "CSGFFileIO.h"


void CSGFFileIO::OnReadSGF(std::ifstream &ifs)
{
	int i;
	bool bCommand, bLegal;
	char c, lpstrBuffer[1024], lpstrMessage[512];
	COMMAND_TYPE ctCommand;
	std::stack<CGameBase::ExtendMove*> stklpemStack;
	bCommand = true;
	bLegal = true;
	i = 0;
	while (!ifs.eof() && bLegal)
	{
		c = '\0';
		ifs.get(c);
		switch (c)
		{
		case '(':
			stklpemStack.push(m_lpemCurrentMove);
			i = 0;
			break;
		case '[':
			if (i != 0)
			{
				lpstrBuffer[i] = 0;
				strcpy(lpstrMessage, lpstrBuffer);
				ctCommand = m_fnClassifyCommand(lpstrMessage);
				i = 0;
			}
			bCommand = false;
			break;
		case ')':
			i = 0;
			while (m_lpemCurrentMove != stklpemStack.top())
			{
				OnBackMove();
			}
			stklpemStack.pop();
			break;
		case ']':
			lpstrBuffer[i] = 0;
			i = 0;
			strcpy(lpstrMessage, lpstrBuffer);
			bLegal = m_fnApplyData(lpstrMessage, ctCommand);
			bCommand = true;
			break;
		case ';':
			i = 0;
			break;
		default:
			if (bCommand)
			{
				if (c >= 'A' && c <= 'Z')
				{
					lpstrBuffer[i] = c;
					++i;
				}
			}
			else
			{
				lpstrBuffer[i] = c;
				++i;
			}
		}
	}
	while (!stklpemStack.empty())
	{
		stklpemStack.pop();
	}
}

bool CSGFFileIO::m_fnApplyData(char *lpstrData, COMMAND_TYPE ctCommand)
{
	DATA_TYPE dtType;
	int x, y;
	bool bLegal;
	bLegal = true;
	dtType = m_fnClassifyData(lpstrData);
	switch (dtType)
	{
	case DT_COORDINATE:
		m_fnConvertCoord(lpstrData, x, y);
		switch (ctCommand)
		{
		case CT_ADD_BLACK:
			if (m_iHandicapPutting < m_nHandicap)
			{
				OnAddHandicap(x, y);
			}
			else
			{
				bLegal = false;
			}
			break;
		case CT_BLACK_MOVE:
			m_scTurnColor = SC_BLACK;
			if (!OnAddMove(x, y))
			{
				bLegal = false;
			}
			break;
		case CT_WHITE_MOVE:
			m_scTurnColor = SC_WHITE;
			if (!OnAddMove(x, y))
			{
				bLegal = false;
			}
			break;
		default:
			break;
		}
		break;
	case DT_NUMBER:
		switch (ctCommand)
		{
		case CT_SIZE:
			if (atoi(lpstrData) != nBoardSize)
			{
				bLegal = false;
			}
			break;
		case CT_HANDICAP:
			m_nHandicap = atoi(lpstrData);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return bLegal;
}


void CSGFFileIO::OnWriteSGF(std::ofstream &ofs)
{
	int i, x, y;
	CGameBase::ExtendMove *lpemVisitor, *lpemRetrospector;
	lpemRetrospector = NULL;
	std::stack<CGameBase::ExtendMove*> stklpemStack;
	ofs << '(';
	ofs << "SZ[" << nBoardSize << ']';
	if (m_iHandicapPutting != 0)
	{
		ofs << "HA[" << m_iHandicapPutting << "]AB";
		for (i = 0; i < m_iHandicapPutting; ++i)
		{
			m_fnCoordinate(m_lplpbpHandicap[i], x, y);
			ofs << '[' << char('a' + x) << char('a' + y) << ']';
		}
	}
	lpemVisitor = m_emBlankMove.child;
	while (!(lpemVisitor == NULL && stklpemStack.empty()))
	{
		while (lpemVisitor != NULL)
		{
			if (lpemVisitor->shorter != NULL)
			{
				stklpemStack.push(lpemVisitor->shorter);
			}
			if (lpemVisitor->shorter != NULL || lpemVisitor->longer != NULL)
			{
				ofs << '(';
			}
			if (lpemVisitor->stone_color == SC_BLACK)
			{
				ofs << ";B" << '[' << char('a' + lpemVisitor->x) << char('a' + lpemVisitor->y) << ']';
			}
			else if (lpemVisitor->stone_color == SC_WHITE)
			{
				ofs << ";W" << '[' << char('a' + lpemVisitor->x) << char('a' + lpemVisitor->y) << ']';
			}
			lpemRetrospector = lpemVisitor;
			lpemVisitor = lpemVisitor->child;
		}
		if (stklpemStack.empty())
		{
			while (lpemRetrospector != &m_emBlankMove)
			{
				if (lpemRetrospector->shorter != NULL || lpemRetrospector->longer != NULL)
				{
					ofs << ')';
				}
				lpemRetrospector = lpemRetrospector->parent;
			}
		}
		else
		{
			lpemVisitor = stklpemStack.top();
			stklpemStack.pop();
			while (lpemRetrospector != lpemVisitor->parent)
			{
				if (lpemRetrospector->shorter != NULL || lpemRetrospector->longer != NULL)
				{
					ofs << ')';
				}
				lpemRetrospector = lpemRetrospector->parent;
			}
		}
	}
	ofs << ')';
}

CSGFFileIO::COMMAND_TYPE CSGFFileIO::m_fnClassifyCommand(char *lpstrCommand)
{
	int len;
	COMMAND_TYPE ctType;
	ctType = CT_NULL;
	len = int(strlen(lpstrCommand));
	switch (len)
	{
	case 1:
		switch (lpstrCommand[0])
		{
		case 'N':
			ctType = CT_NAME;
			break;
		case 'C':
			ctType = CT_COMMENT;
			break;
		case 'B':
			ctType = CT_BLACK_MOVE;
			break;
		case 'W':
			ctType = CT_WHITE_MOVE;
			break;
		}
		break;
	case 2:
		if (strcmp(lpstrCommand, "SZ") == 0)
		{
			ctType = CT_SIZE;
		}
		else if (strcmp(lpstrCommand, "HA") == 0)
		{
			ctType = CT_HANDICAP;
		}
		else if (strcmp(lpstrCommand, "RE") == 0)
		{
			ctType = CT_RESULT;
		}
		else if (strcmp(lpstrCommand, "AB") == 0)
		{
			ctType = CT_ADD_BLACK;
		}
		break;
	default:
		ctType = CT_NULL;
		break;
	}
	return ctType;
}

CSGFFileIO::DATA_TYPE CSGFFileIO::m_fnClassifyData(char *lpstrData)
{
	int len, i;
	DATA_TYPE dtType;
	len = int(strlen(lpstrData));
	dtType = DT_STRING;
	switch (len)
	{
	case 0:
		dtType = DT_COORDINATE;
		break;
	case 1:
		if ((lpstrData[0] >= '0') && (lpstrData[0] <= '9'))
		{
			dtType = DT_NUMBER;
		}
		break;
	case 2:
		if ((lpstrData[0] >= '0') && (lpstrData[0] <= '9') && (lpstrData[1] >= '0') && (lpstrData[1] <= '9'))
		{
			dtType = DT_NUMBER;
		}
		else if ((lpstrData[0] >= 'a') && (lpstrData[0] < 'a' + nBoardSize) || (lpstrData[1] >= 'A') && (lpstrData[1] < 'A' + nBoardSize))
		{
			dtType = DT_COORDINATE;
		}
		else if (lpstrData[0] == 't' && lpstrData[1] == 't')
		{
			dtType = DT_COORDINATE;
		}
		break;
	default:
		dtType = DT_NUMBER;
		for (i = 0; i < len; ++i)
		{
			if (!((lpstrData[i] >= '0' && lpstrData[i] <= '9') || lpstrData[i] == '.'))
			{
				dtType = DT_STRING;
				break;
			}
		}
		break;
	}
	return dtType;
}

void CSGFFileIO::m_fnConvertCoord(char *lpstrCommand, int &x, int &y)
{
	int len;
	len = int(strlen(lpstrCommand));
	if (len == 0 || (nBoardSize < 20 && lpstrCommand[0] == 't' && lpstrCommand[1] == 't'))
	{
		x = nBoardSize;
		y = 0;
	}
	else
	{
		if (lpstrCommand[0] >= 'a' && lpstrCommand[0] < 'a' + nBoardSize)
		{
			x = lpstrCommand[0] - 'a';
		}
		else if (lpstrCommand[0] >= 'A' && lpstrCommand[0] < 'A' + nBoardSize)
		{
			x = lpstrCommand[0] - 'A';
		}
		else
		{
			x = -1;
		}
		if (lpstrCommand[1] >= 'a' && lpstrCommand[1] < 'a' + nBoardSize)
		{
			y = lpstrCommand[1] - 'a';
		}
		else if (lpstrCommand[1] >= 'A' && lpstrCommand[1] < 'A' + nBoardSize)
		{
			y = lpstrCommand[1] - 'A';
		}
		else
		{
			y = -1;
		}
	}
}