#ifndef MAP_H
#define MAP_H

class Map {
    static const int height = 5;
    std::string m_field[height];

    char check_win();
protected:
    static const char SPACE = ' ';
    int m_filled = 0;// aka size and moves count
    char map[3][3];
    
    void v_fill_point(int x, int y, char value);
public:
    Map():m_field{"_|0|1|2|y",
                "0| | | |",
                "1| | | |",
                "2| | | |",
                "x" }, 
           map{ {SPACE, SPACE, SPACE,},
                {SPACE, SPACE, SPACE,},
                {SPACE, SPACE, SPACE,}} {
    }
    void print_field() const;
    bool fill_point(int x, int y, char value);
    bool win();
};

#endif // MAP_H
