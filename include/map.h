#ifndef MAP_H
#define MAP_H

class Map {
    static const int height = 5;
    char _map[3][3] = {};

    int m_filled = 0;// aka size and moves count

    char check_win();
protected:
    void v_fill_point(int x, int y, char value);
    void init() {
        _map[0][0] = _map[0][1] = _map[0][2] = _map[1][0] = _map[1][1] = _map[1][2] =
        _map[2][0] = _map[2][1] = _map[2][2] = SPACE;
    }
public:
    static const char SPACE = ' ';

    Map() {
        init();
    }
    void print_field() const;
    bool fill_point(int x, int y, char value);
    bool win();

    char map(int x, int y) const {
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
