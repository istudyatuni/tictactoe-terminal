#ifndef MAP_H
#define MAP_H

#include <string>
using std::string;

class Map {
    int width = 9, height = 5;
    string field[5];

    char check_win();
public:
    Map():field{"_|0|1|2|Y",
                "0| | | |",
                "1| | | |",
                "2| | | |",
                "X" } {
    }
    void print_field();
    bool fill_point(int x, int y, char value);
    bool win();
};

#endif // MAP_H
