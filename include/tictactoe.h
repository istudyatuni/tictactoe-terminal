#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <iostream>
#include "map.h"

class Tictactoe:
    public Map {
    char player, env;
    char win_right_now(char player, char opponent);
    bool check_line(char a, char b,int x, int y,
                char p, char o);//x, y for map[][]
public:
    Tictactoe() {
    }
    void pvp();
    void pve();
};

#endif // TIC_TAC_TOE_H
