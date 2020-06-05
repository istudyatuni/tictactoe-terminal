#include <iostream>
#include "tictactoe.h"
using std::cout;
using std::cin;

bool Tictactoe::check_line(char a, char b, int x, int y,
                    char p, char o) {//x, y for map[][]
    if (map[x][y] == ' ' && a == b) {
        if (a == p) {//player может выиграть
            map[x][y] = p;
            return true;
        }
        if (a == o) {//противник player-а может выиграть
            map[x][y] = p;
            return true;
        }
    }
    return false;
}

char Tictactoe::win_right_now(char player, char opponent) {
    char a, b;//что будет сравнивать
    for (int i = 0; i < 3; ++i) {//перебираем строки/столбцы
        for (int j = 0; j < 3; ++j) {//перебираем элементы внутри
            // rows
            a = map[i][(j + 1) % 3];
            b = map[i][(j + 2) % 3];
            if (check_line(a, b, i, j, player, opponent)) {
                return player;
            }
            // columns
            a = map[(j + 1) % 3][i];
            b = map[(j + 2) % 3][i];
            if (check_line(a, b, j, i, player, opponent)) {
                return player;
            }
        }
        // main diagonal
        a = map[(i + 1) % 3][(i + 1) % 3];
        b = map[(i + 2) % 3][(i + 2) % 3];
        if (check_line(a, b, i, i, player, opponent)) {
            return player;
        }
        // anti-diagonal
        a = map[(i + 1) % 3][(i + 2) * 2 % 3];
        b = map[(i + 2) % 3][(i + 3) * 2 % 3];
        if (check_line(a, b, i, (i + 1) * 2 % 3, player, opponent)) {
            return player;
        }
    }
    return ' ';
}

void Tictactoe::pvp() {
    int x, y;
    char s, player = 'X';
    cout << "Enter coordinates as 1,2. For stop enter -1\n";
    print_field();
    do {
        s = '.';// disable infinity loop when tap ctrl+d
        cout << player << " move: ";
        cin >> x;
        if (x == -1) {
            cout << "exit\n";
            break;
        }
        cin >> s >> y;
        if (fill_point(x, y, player)) {
            print_field();
            if (win()) {
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
}

void Tictactoe::pve() {
    player = 'X';
    env = '0';
    fill_point(1, 1, env);
    fill_point(0, 2, env);
    //fill_point(1, 2, env);
    fill_point(2, 1, player);
    fill_point(1, 2, player);
    print_field();
    char t = win_right_now(env, player);
    print_field();
    cout << "t: " << t << '\n';
}