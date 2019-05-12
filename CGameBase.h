#ifndef CGAMEBASE_H
#define CGAMEBASE_H
#include <string.h>
#include <vector>
#define STANDARD_BOARD_SIZE 19
enum StoneColor
{
    SC_NULL = 0,
    SC_BLACK,
    SC_WHITE,
};
extern int nBoardSize;
namespace CGameBase
{
    struct BasePosition
    {
        int x, y;
		BasePosition()
		{
			x = -1;
			y = -1;
		}
        bool import_position(char *position_info)
        {
            bool bLegal;
            bLegal = true;
            if (strcmp(position_info, "pass") == 0 || strcmp(position_info, "Pass") == 0 || strcmp(position_info, "PASS") == 0)
            {
                x = nBoardSize;
                y = 0;
            }
			else if (strcmp(position_info, "resign") == 0 || strcmp(position_info, "Resign") == 0 || strcmp(position_info, "RESIGN") == 0)
			{
				x = nBoardSize;
				y = 1;
			}
            else if (position_info[0] >= 'a' && position_info[0] < 'i')
            {
                x = position_info[0] - 'a';
            }
            else if (position_info[0] > 'i' && position_info[0] <= 'z')
            {
                x = position_info[0] - 'b';
            }
            else if (position_info[0] >= 'A' && position_info[0] < 'I')
            {
                x = position_info[0] - 'A';
            }
            else if (position_info[0] > 'I' && position_info[0] <= 'Z')
            {
                x = position_info[0] - 'B';
            }
            else
            {
                bLegal = false;
            }
            if (bLegal && x != nBoardSize)
            {
                if (position_info[1] > '0' && position_info[1] <= '9' && position_info[2] == '\0')
                {
                    y = nBoardSize - (position_info[1] - '0');
                }
                else if ((position_info[1] == '1' || position_info[1] == '2') && position_info[2] >= '0' && position_info[2] <= '9' && position_info[3] == '\0')
                {
                    y = nBoardSize - (position_info[1] - '0') * 10 - (position_info[2] - '0');
                }
                else
                {
                    bLegal = false;
                }
            }
            return bLegal;
        }
        bool export_position(char *position_info)
        {
            bool bLegal = (x >= 0 && x < nBoardSize && y >= 0 && y < nBoardSize) || (x == nBoardSize && y == 0) || (x == nBoardSize && y == 1);
            if (bLegal)
            {
                if (x == nBoardSize && y == 0)
                {
                    strcpy(position_info, "pass");
                }
				else if (x == nBoardSize && y == 1)
				{
					strcpy(position_info, "resign");
				}
                else
                {
                    if (x < 8)
                    {
                        position_info[0] = 'A' + x;
                    }
                    else
                    {
                        position_info[0] = 'B' + x;
                    }
                    if (nBoardSize - y < 10)
                    {
                        position_info[1] = '0' + (nBoardSize - y) % 10;
                        position_info[2] = '\0';
                    }
                    else
                    {
                        position_info[1] = '0' + (nBoardSize - y) / 10;
                        position_info[2] = '0' + (nBoardSize - y) % 10;
                        position_info[3] = '\0';
                    }
                }
            }
            return bLegal;
        }
    };
    struct BaseMove: public BasePosition
    {
		BaseMove()
		{
			stone_color = SC_NULL;
		}
        StoneColor stone_color;
        bool import_move(char *move_info)
        {
            bool bLegal;
            int len, i;
            bLegal = true;
            if ((move_info[0] == 'w' || move_info[0] == 'W')&&move_info[1] == ' ')
            {
                stone_color = SC_BLACK;
            }
            else if ((move_info[0] == 'b' || move_info[0] == 'B') && move_info[1] == ' ')
            {
                stone_color = SC_WHITE;
            }
            else
            {
                bLegal = false;
                stone_color = SC_NULL;
            }
            if (bLegal)
            {
                len = int(strlen(move_info));
                for (i = 2; i < len - 1; ++i)
                {
                    if (move_info[i] != ' ')
                    {
                        break;
                    }
                }
                if (i < len - 1)
                {
                    bLegal = import_position(move_info + i);
                }
            }
            if (!bLegal)
            {
                stone_color = SC_NULL;
                x = -2;
                y = -2;
            }
            return bLegal;
        }
        bool export_move(char *move_info)
        {
            bool bLegal;
            bLegal = true;
            if ((stone_color == SC_BLACK || stone_color == SC_WHITE) && ((x >= 0 && x < nBoardSize && y >= 0 && y < nBoardSize) || (x == nBoardSize && y == 0) || (x == nBoardSize && y == 1)))
            {
                if (stone_color == SC_WHITE)
                {
                    move_info[0] = 'w';
                }
                if (stone_color == SC_BLACK)
                {
                    move_info[0] = 'b';
                }
                move_info[1] = ' ';
                export_position(move_info + 2);
            }
            else
            {
                bLegal = false;
            }
            return bLegal;
        }
    };
    struct BoardPoint
    {
        BoardPoint()
        {
            stone_color = SC_NULL;
            visits = 0;
            win_rate = -1;
            order = -1;
            mark = 0;
			pv_len = 0;
        }
        int mark;
        StoneColor stone_color;
        int visits;
        int win_rate;
        int prior;
		int lcb;
        int order;
		BasePosition pv[64];
		int pv_len;
    };
	struct Remove
	{
		Remove()
		{
			bp = NULL;
		}
		BoardPoint *bp;
		bool empty()
		{
			return (bp == NULL);
		}
		void release()
		{
			bp = NULL;
		}
	};
    struct ExtendMove: public BaseMove
    {
		ExtendMove()
		{
			x = -1;
			y = -1;
			remove_data = NULL;
			remove_len = 0;
			step = 0;
			branch = 0;
			depth = 0;
			parent = child = longer = shorter = NULL;
		}
		ExtendMove *parent, *child, *longer, *shorter;
		Remove *remove_data;
		int remove_len, step, branch, depth;
		bool empty()
		{
			return (x == -1 && y == -1);
		}
		void release()
		{
			x = -1;
			y = -1;
			remove_data = NULL;
			remove_len = 0;
			step = 0;
			branch = 0;
			depth = 0;
			parent = child = longer = shorter = NULL;
		}
		ExtendMove* search(int x, int y)
		{
			ExtendMove *lpem_visitor;
			lpem_visitor = child;
			while (lpem_visitor != NULL)
			{
				if (lpem_visitor->x == x && lpem_visitor->y == y)
				{
					break;
				}
				lpem_visitor = lpem_visitor->shorter;
			}
			return lpem_visitor;
		}
    };
};



#endif // CGAMEBASE_H
