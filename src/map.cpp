#include <iostream>
#include <string>

#include "map.h"
using std::cout;

void Map::set_field() {
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            v_fill_point(i, j, map[i][j]);
        }
    }
}

void Map::v_fill_point(int x, int y, char value) {
    bool t = fill_point(x, y, value);
    return;
}

char Map::check_win() {
    for (int i = 0; i < 3; ++i) {//перебор строк/столбцов
        //rows
        if (map[i][0] == map[i][1] && map[i][1] == map[i][2]) {
            return map[i][0];
        }
        // columns
        if (map[0][i] == map[1][i] && map[1][i] == map[2][i]){
            return map[0][i];
        }
    }
    if (map[0][0] == map[1][1] && map[1][1] == map[2][2]) {
        return map[1][1];
    }
    if (map[0][2] == map[1][1] && map[1][1] == map[2][0]) {
        return map[1][1];
    }
    return ' ';
}
void Map::print_field() {
    set_field();
    for (int i = 0; i < height; ++i){
        cout << field[i] << '\n';
    }
}
bool Map::fill_point(int x, int y, char value) {
    if ((x > 2 || x < 0) && (y > 2 || y < 0)) {
        return false;
    }
    x++;
    y = (y + 1) * 2;
    if (field[x][y] != ' '){
        return false;
    }
    field[x][y] = value;
    map[x - 1][y / 2 - 1] = value;
    return true;
}
bool Map::win() {
    char w = check_win();
    cout << "filled: " << filled << '\n';
    if (w != ' ') {
        cout << '\n' << w << " is win!\n";
        return true;
    }
    if (filled == 9) {
        cout << "Drawn game\n";
        return true;
    }
    return false;
}