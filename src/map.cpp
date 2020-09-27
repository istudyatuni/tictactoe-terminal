#include <cstdio>
#include "map.h"

void Map::v_fill_point(int x, int y, char value) {
    bool t = fill_point(x, y, value);
    // for suppress -Wunused-variable, it's do nothing
    x = t;
    return;
}

char Map::check_win() {
    for (int i = 0; i < 3; ++i) {//перебор строк/столбцов
        //rows
        if (map(i, 0) == map(i, 1) && map(i, 1) == map(i, 2)) {
            return map(i, 0);
        }
        // columns
        if (map(0, i) == map(1, i) && map(1, i) == map(2, i)){
            return map(0, i);
        }
    }
    if (map(0, 0) == map(1, 1) && map(1, 1) == map(2, 2)) {
        return map(1, 1);
    }
    if (map(0, 2) == map(1, 1) && map(1, 1) == map(2, 0)) {
        return map(1, 1);
    }
    return SPACE;
}
void Map::print_field() const {
    const char* CYAN = "\x1B[96m";
    const char* NC   = "\033[0m"; // No Color
    char e;
    printf("x\t\b\by 0\t1\t2\n\n");
    for (int i = 0; i < 3; ++i){
        printf("%i\t", i);
        for (int j = 0; j < 3; ++j) {
            e = map(i, j);
            if (e == SPACE) {
                e = '.';
            }
            // print with cyan color
            printf("%s%c%s\t", CYAN, e, NC);
        }
        printf("\n\n");
    }
}
bool Map::fill_point(int x, int y, char value) {
    if ((x > 2 || x < 0) && (y > 2 || y < 0)) {
        return false;
    }
    if (map(x, y) != SPACE){
        return false;
    }
    _map[x][y] = value;
    return true;
}
bool Map::win() {
    char w = check_win();
    if (w != SPACE) {
        printf("\n%c wins!\n", w);
        return true;
    }
    if (m_filled == 9) {
        printf("Drawn game\n");
        return true;
    }
    return false;
}
