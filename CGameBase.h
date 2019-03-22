#ifndef CGAMEBASE_H
#define CGAMEBASE_H
#include <string.h>
#include <vector>
namespace CGameBase
{
    enum StoneColor
    {
        SC_NULL = 0,
        SC_BLACK,
        SC_WHITE,
    };
    struct BasePosition
    {
        int x, y;
        bool import_position(char *position_info)
        {
            bool bLegal;
            bLegal = true;
            if (strcmp(position_info, "pass") == 0)
            {
                x = -1;
                y = -1;
            }
            else if (position_info[0] >= 'a' && position_info[0] < 'i')
            {
                x = position_info[0] - 'a';
            }
            else if (position_info[0] > 'i' && position_info[0] < 'u')
            {
                x = position_info[0] - 'b';
            }
            else if (position_info[0] >= 'A' && position_info[0] < 'I')
            {
                x = position_info[0] - 'A';
            }
            else if (position_info[0] > 'I' && position_info[0] < 'U')
            {
                x = position_info[0] - 'B';
            }
            else
            {
                bLegal = false;
            }
            if (bLegal && x != -1)
            {
                if (position_info[1] > '0' && position_info[1] <= '9' && position_info[2] == '\0')
                {
                    y = 18 - (position_info[1] - '1');
                }
                else if (position_info[1] == '1' && position_info[2] >= '0' && position_info[2] <= '9' && position_info[3] == '\0')
                {
                    y = 9 - (position_info[2] - '0');
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
            bool bLegal = (x >= 0 && x < 19 && y >= 0 && y < 19) || (x == -1 && y == -1);
            if (bLegal)
            {
                if (x == -1 && y == -1)
                {
                    strcpy(position_info, "pass");
                }
                else
                {
                    if (x < 8)
                    {
                        position_info[0] = 'a' + x;
                    }
                    else
                    {
                        position_info[0] = 'b' + x;
                    }
                    if (y > 9)
                    {
                        position_info[1] = '9' - (y - 10);
                        position_info[2] = '\0';
                    }
                    else
                    {
                        position_info[1] = '1';
                        position_info[2] = '9' - y;
                        position_info[3] = '\0';
                    }
                }
            }
            return bLegal;
        }
    };
    struct BaseMove: public BasePosition
    {
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
                len = strlen(move_info);
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
            if ((stone_color == SC_BLACK || stone_color == SC_WHITE) && ((x >= 0 && x < 19 && y >= 0 && y < 19) || (x == -1 && y == -1)))
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
    struct ExtendMove: public BaseMove
    {
        std::vector<BasePosition> vecRemoved;
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
        }
        int mark;
        StoneColor stone_color;
        int visits;
        int win_rate;
        int prior;
        int order;
        std::vector<BasePosition> pv;
    };
};




#endif // CGAMEBASE_H
