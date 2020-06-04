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
            }
        }
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
        if ((x > 2 || x < 0) && (y > 2 || y < 0)) {
            return false;
        }
        x++;
        y = (y + 1) * 2;
        if (field[x][y] != ' '){
            return false;
        }
        field[x][y] = value;
        return true;
    }
    bool win() {
        char w = check_win();
        if (w != ' ') {
            cout << '\n' << w << " is win!\n";
            return true;
        }
        return false;
    }
};

int main() {
    Map map;
    int x, y;
    char s, player = 'X';
    cout << "Enter coordinates as 1,2. For stop enter -1\n";
    map.print_field();
    do {
        s = '.';// disable infinity loop when tap ctrl+d
        cout << player << " move: ";
        cin >> x >> s >> y;
        if (x == -1) {
            break;
        }
        if (map.fill_point(x, y, player)) {
            map.print_field();
            if (map.win()) {
                break;
            }
            if (player == 'X') {
                player = '0';
            } else { // player == '0'
                player = 'X';
            }
        } else {
            cout << "Incorrect. Try again\n";
        }
    } while(s == ',');
    return 0;
}