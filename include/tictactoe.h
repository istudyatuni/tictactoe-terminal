#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <iostream>
#include "map.h"

enum class Place {
    NONE,
    CENTER,
    ANGLE,
    SIDE
};

class Tictactoe: public Map
{
    char m_player, m_env;
    int m_firstx, m_firsty; // for pve
    
    Place m_move;
    Place m_first_move = Place::NONE;

    bool win_right_now(char player, char opponent);
    bool win_check_line(char a, char b,int x, int y,
                char p, char o);//x, y for map[][]
    void env_move(int x, int y);

    Place check_place(int x, int y);

    void pvp();
    void pve();
public:
    void play();
};

#endif // TIC_TAC_TOE_H
