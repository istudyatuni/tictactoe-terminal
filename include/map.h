#ifndef MAP_H
#define MAP_H

class Map {
    static const int height = 5;
    std::string m_field[height];
    char _map[3][3];

    int m_filled = 0;// aka size and moves count

    char check_win();
protected:
    void v_fill_point(int x, int y, char value);
public:
    static const char SPACE = ' ';

    Map():m_field{"_|0|1|2|y",
                  "0| | | |",
                  "1| | | |",
                  "2| | | |",
                 "x" }, 
           _map{{ SPACE, SPACE, SPACE },
                { SPACE, SPACE, SPACE },
                { SPACE, SPACE, SPACE }} {
    }
    void print_field() const;
    bool fill_point(int x, int y, char value);
    bool win();

    char map(int x, int y) {
        return _map[x][y];
    }
    int filled() {
        return m_filled;
    }
    void inc_filled() {
        m_filled++;
    }
};

#endif // MAP_H
