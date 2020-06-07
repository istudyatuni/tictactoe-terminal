#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <iostream>
#include "map.h"

class Tictactoe: public Map
{
    char m_player, m_env;
    int m_firstx, m_firsty; // for pve
    
    int m_move;
    int m_first_move = NONE;

    bool win_right_now(char player, char opponent);
    bool win_check_line(char a, char b,int x, int y,
                char p, char o);//x, y for map[][]
    void env_move(int x, int y);

    enum Place { NONE, CENTER, ANGLE, SIDE };
    int check_place(int x, int y);

    void pvp();
    void pve();
public:
    void play();
};

#endif // TIC_TAC_TOE_H
