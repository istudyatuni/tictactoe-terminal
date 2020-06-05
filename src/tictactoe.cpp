#include <iostream>
#include "tictactoe.h"
using std::cout;
using std::cin;

bool Tictactoe::win_check_line(char a, char b, int x, int y,
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

bool Tictactoe::win_right_now(char player, char opponent) {
    char a, b;//что будет сравнивать
    for (int i = 0; i < 3; ++i) {//перебираем строки/столбцы
        for (int j = 0; j < 3; ++j) {//перебираем элементы внутри
            // rows
            a = map[i][(j + 1) % 3];
            b = map[i][(j + 2) % 3];
            if (win_check_line(a, b, i, j, player, opponent)) {
                return true;
            }
            // columns
            a = map[(j + 1) % 3][i];
            b = map[(j + 2) % 3][i];
            if (win_check_line(a, b, j, i, player, opponent)) {
                return true;
            }
        }
        // main diagonal
        a = map[(i + 1) % 3][(i + 1) % 3];
        b = map[(i + 2) % 3][(i + 2) % 3];
        if (win_check_line(a, b, i, i, player, opponent)) {
            return true;
        }
        // anti-diagonal
        a = map[(i + 1) % 3][(i + 2) * 2 % 3];
        b = map[(i + 2) % 3][(i + 3) * 2 % 3];
        if (win_check_line(a, b, i, (i + 1) * 2 % 3, player, opponent)) {
            return true;
        }
    }
    return false;
}

int Tictactoe::check_place(int x, int y) {
    // in map 3x3
    if ((x == 0 && y == 0) ||
        (x == 0 && y == 2) ||
        (x == 2 && y == 0) ||
        (x == 2 && y == 2)) {
        return ANGLE;
    }
    if ((x == 0 && y == 1) ||
        (x == 1 && y == 0) ||
        (x == 2 && y == 1) ||
        (x == 1 && y == 2)) {
        return SIDE;
    } else { // x == 1 && y == 1
        return CENTER;
    }
}

void Tictactoe::env_move(int x, int y) {
    if (win_right_now(env, player)) {
        print_field();
        return;
    }
    if (first_move == CENTER) {
        int a, b;
        for (int i = 0; i < 9; ++i) {
            a = i / 3;
            b = i % 3;
            if (map[a][b] == ' ' && check_place(a, b) == ANGLE) {
                v_fill_point(a, b, env);
                print_field();
                return;
            }
        }
        //если все углы заняты
        for (int i = 0; i < 9; ++i) {
            a = i / 3;
            b = i % 3;
            if (map[a][b] == ' ' && check_place(a, b) == SIDE) {
                v_fill_point(a, b, env);
                print_field();
                return;
            }
        }
    }
    if (first_move == ANGLE) {
        if (filled == 1) {
            // move to center
            v_fill_point(1, 1, env);
            print_field();
            return;
        }
        if (move == ANGLE) {
            // situation:
            // --X
            // -0-
            // X--
            // just random SIDE place
            v_fill_point(0, 1, env);
            print_field();
            return;
        }
        if (move == SIDE) {
            int a, b;
            // place 0 near X on the SIDE:
            // --X
            // -0-
            // -X0 <- here - don't work correctly,
            // but env don't lose
            a = y;
            b = firstx;
            if (check_place(a, b) == ANGLE) {
                v_fill_point(a, b, env);
                print_field();
                return;
            }
            a = firsty;
            b = x;
            if (check_place(a, b) == ANGLE) {
                v_fill_point(a, b, env);
                print_field();
                return;
            }
        }
    }
    if (first_move == SIDE) {
        if (filled == 1) {
            // move to center
            v_fill_point(1, 1, env);
            print_field();
            return;
        }
        if (move == ANGLE) {
            if (filled == 5) {
                // in this case:
                // 0X0 <- set in angle
                // X0-
                // --X
                // один из двух углов ниже занят, так что
                // не сломается
                cout << "fl\n";
                v_fill_point(0, 0, env);
                v_fill_point(2, 0, env);
                print_field();
                return;
            }
            if (x == 0 && x == y) {
                // angle (0, 0)
                v_fill_point(2, 2, env);
                print_field();
                return;
            }
            if (x != y) {
                // angle (x, y)
                v_fill_point(y, x, env);
                print_field();
                return;
            }
            if (x == 2 && x == y) {
                // angle (2, 2)
                v_fill_point(0, 0, env);
                print_field();
                return;
            }
        }
        if (move == SIDE) {
            if (x == firstx || y == firsty) {
                // противоположная сторона
                // just random angle
                v_fill_point(0, 0, env);
                print_field();
                return;
            }
            // position as:
            // -X0 <- here
            // -0X
            // ---
            v_fill_point(x + firstx - 1, y + firsty - 1, env);
            print_field();
            return;
        }
    }
}

void Tictactoe::pvp() {
    int x, y;
    char s, player = 'X';
    cout << "Enter coordinates as x,y. For stop enter -1\n";
    print_field();
    do {
        s = '.';// disable infinity loop when tap ctrl+d
        cout << player << " move: ";
        cin >> x;
        if (x == -1) {
            cout << "Drawn game\n";
            break;
        }
        cin >> s >> y;
        if (fill_point(x, y, player)) {
            filled++;
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
    int x, y;
    char s;
    cout << "Enter coordinates as x,y. For stop enter -1\n";
    print_field();
    do {
        s = '.';
        cout << player << " move: ";
        cin >> x;
        if (x == -1) {
            cout << "Drawn game\n";
            break;
        }
        cin >> s >> y;
        if (first_move == NONE) {
            // remember first player move
            first_move = check_place(x, y);
            firstx = x;
            firsty = y;
        }
        move = check_place(x, y);
        if (fill_point(x, y, player)) {
            filled++;
            print_field();
            if (win()) {
                break;
            }
            env_move(x, y);
            filled++;
            if (win()) {
                break;
            }
        } else {
            cout << "Incorrect. Try again\n";
        }
    } while(s == ',');
}

void Tictactoe::play() {
    int mode;
    cout << "Choose mode (1 - pve, 2 - pvp): ";
    cin >> mode;
    if (mode == 1) {
        pve();
    } else if (mode == 2) {
        pvp();
    } else {
        cout << "Incorrect\n";
    }
}