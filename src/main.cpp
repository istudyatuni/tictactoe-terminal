#include <iostream>
#include <string>
using namespace std;

class Map {
    int width = 9, height = 5;
    string field[5];

    char check_win() {
        char map[3][3];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                map[i][j] = field[i + 1][(j + 1) * 2];
                //cout << map[i][j];
            }
            //cout << '\n';
        }
        for (int i = 0; i < 3; ++i) {//перебор строк/столбцов
            //rows
            if (map[i][0] == map[i][1] && map[i][1] == map[i][2]) {
                //cout << map[i][j] << '.' << map[i][j + 1] << '.';
                //cout << map[i][j + 2] << '\n';
                //cout << i << '.' << j << ",1: " << map[i][j];
                return map[i][0];
            }
            // columns
            if (map[0][i] == map[1][i] && map[1][i] == map[2][i]){
                //cout << "2: " << map[j][i];
                return map[0][i];
            }
        }
        if (map[0][0] == map[1][1] && map[1][1] == map[2][2]) {
            //cout << "3: " << map[1][1];
            return map[1][1];
        }
        if (map[0][2] == map[1][1] && map[1][1] == map[2][0]) {
            //cout << "4: " << map[1][1];
            return map[1][1];
        }
        return ' ';
    }
public:
    Map():field{"_|0|1|2|Y",
                "0| | | |",
                "1| | | |",
                "2| | | |",
                "X" } {
    }
    void print_field() {
        for (int i = 0; i < height; ++i){
            cout << field[i] << '\n';
        }
    }
    bool fill_point(int x, int y, char value) {
        x++;
        y = (y + 1) * 2;
        if (field[x][y] != ' '){
            return false;
        }
        field[x][y] = value;
        return true;
    }
    void win() {
        char w = check_win();
        if (w != ' ') {
            cout << '\n' << w << " is win!\n";
        }
    }
};

int main() {
    Map map;
    map.fill_point(0, 1, 'X');
    map.fill_point(0, 2, 'X');
    map.fill_point(0, 0, 'X');
    map.fill_point(1, 2, '0');
    map.print_field();
    map.win();
    return 0;
}