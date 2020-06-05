#ifndef MAP_H
#define MAP_H

#include <string>
using std::string;

class Map {
    int width = 9, height = 5;
    string field[5];

    char check_win();
protected:
    int filled = 0;// aka size and moves count
    char map[3][3];
    void set_field();
    void v_fill_point(int x, int y, char value);
public:
    Map():field{"_|0|1|2|y",
                "0| | | |",
                "1| | | |",
                "2| | | |",
                "x" }, 
           map{ {' ', ' ', ' ',},
                {' ', ' ', ' ',},
                {' ', ' ', ' ',}} {
    }
    void print_field();
    bool fill_point(int x, int y, char value);
    bool win();
};

#endif // MAP_H
