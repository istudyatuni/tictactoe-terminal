#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <iostream>
#include "map.h"

class Tictactoe:
    public Map {
    char player, env;
    bool win_right_now(char player, char opponent);
    bool check_line(char a, char b,int x, int y,
                char p, char o);//x, y for map[][]
    void env_move(int x, int y);

    enum Place { NONE, CENTER, ANGLE, SIDE };
    int move;
    int first_move = NONE;
    int check_place(int x, int y);
public:
    Tictactoe() {
    }
    void pvp();
    void pve();
};

#endif // TIC_TAC_TOE_H
