#include <iostream>
#include "tictactoe.h"

bool Tictactoe::win_check_line(char a, char b, int x, int y,
                    char p, char o) {//x, y for map[][]
    if (map(x, y) == SPACE && a == b) {
        if (a == p) {//player может выиграть
            v_fill_point(x, y, p);
            return true;
        }
        if (a == o) {//противник player-а может выиграть
            v_fill_point(x, y, p);
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
            a = map(i, (j + 1) % 3);
            b = map(i, (j + 2) % 3);
            if (win_check_line(a, b, i, j, player, opponent)) {
                return true;
            }
            // columns
            a = map((j + 1) % 3, i);
            b = map((j + 2) % 3, i);
            if (win_check_line(a, b, j, i, player, opponent)) {
                return true;
            }
        }
        // main diagonal
        a = map((i + 1) % 3, (i + 1) % 3);
        b = map((i + 2) % 3, (i + 2) % 3);
        if (win_check_line(a, b, i, i, player, opponent)) {
            return true;
        }
        // anti-diagonal
        a = map((i + 1) % 3, (i + 2) * 2 % 3);
        b = map((i + 2) % 3, (i + 3) * 2 % 3);
        if (win_check_line(a, b, i, (i + 1) * 2 % 3, player, opponent)) {
            return true;
        }
    }
    return false;
}

Place Tictactoe::check_place(int x, int y) {
    // in map 3x3
    if ((x == 0 && y == 0) ||
        (x == 0 && y == 2) ||
        (x == 2 && y == 0) ||
        (x == 2 && y == 2)) {
        return Place::ANGLE;
    }
    if ((x == 0 && y == 1) ||
        (x == 1 && y == 0) ||
        (x == 2 && y == 1) ||
        (x == 1 && y == 2)) {
        return Place::SIDE;
    } else { // x == 1 && y == 1
        return Place::CENTER;
    }
}

void Tictactoe::env_move(int x, int y) {
    if (win_right_now(m_env, m_player)) {
        return;
    }
    if (m_first_move == Place::CENTER) {
        int a, b;
        for (int i = 0; i < 9; ++i) {
            a = i / 3;
            b = i % 3;
            if (map(a, b) == SPACE && check_place(a, b) == Place::ANGLE) {
                v_fill_point(a, b, m_env);
                return;
            }
        }
        //если все углы заняты
        for (int i = 0; i < 9; ++i) {
            a = i / 3;
            b = i % 3;
            if (map(a, b) == SPACE && check_place(a, b) == Place::SIDE) {
                v_fill_point(a, b, m_env);
                return;
            }
        }
    }
    if (m_first_move == Place::ANGLE) {
        if (filled() == 1) {
            // move to center
            v_fill_point(1, 1, m_env);
            return;
        }
        if (m_move == Place::ANGLE) {
            // situation:
            // --X
            // -0-
            // X--
            // just random SIDE place
            v_fill_point(0, 1, m_env);
            return;
        }
        if (m_move == Place::SIDE) {
            int a, b;
            // place 0 near X on the SIDE:
            // --X
            // -0-
            // -X0 <- here - don't work correctly,
            // but env don't lose
            a = y;
            b = m_firstx;
            if (check_place(a, b) == Place::ANGLE) {
                v_fill_point(a, b, m_env);
                return;
            }
            a = m_firsty;
            b = x;
            if (check_place(a, b) == Place::ANGLE) {
                v_fill_point(a, b, m_env);
                return;
            }
        }
    }
    if (m_first_move == Place::SIDE) {
        if (filled() == 1) {
            // move to center
            v_fill_point(1, 1, m_env);
            return;
        }
        if (m_move == Place::ANGLE) {
            if (filled() == 5) {
                // in this case:
                // 0X0 <- set in angle
                // X0-
                // --X
                // один из двух углов ниже занят, так что
                // не сломается
                v_fill_point(0, 0, m_env);
                v_fill_point(2, 0, m_env);
                return;
            }
            if (x == 0 && x == y) {
                // angle (0, 0)
                v_fill_point(2, 2, m_env);
                return;
            }
            if (x != y) {
                // angle (x, y)
                v_fill_point(y, x, m_env);
                return;
            }
            if (x == 2 && x == y) {
                // angle (2, 2)
                v_fill_point(0, 0, m_env);
                return;
            }
        }
        if (m_move == Place::SIDE) {
            if (x == m_firstx || y == m_firsty) {
                // противоположная сторона
                // just random angle
                v_fill_point(0, 0, m_env);
                return;
            }
            // position as:
            // -X0 <- here
            // -0X
            // ---
            v_fill_point(x + m_firstx - 1, y + m_firsty - 1, m_env);
            return;
        }
    }
}

void Tictactoe::pvp() {
    int x, y;
    char s, player = 'X';

    const char* RED = "\x1B[31m";
    const char* NC   = "\033[0m"; // No Color

    system(CLEAR);
    printf("\n%sEnter coordinates as x,y.%s For stop enter -1\n", RED, NC);
    print_field();
    do {
        s = '.';// disable infinity loop when tap ctrl+d
        printf("%c move: ", player);
        scanf("%i", &x);
        if (x == -1) {
            printf("Interrupt\n");
            break;
        }
        scanf("%c%i", &s, &y);
        if (fill_point(x, y, player)) {
            system(CLEAR);

            inc_filled();
            printf("Player %c move:\n", player);
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
            printf("Incorrect. Try again\n");
        }
    } while(s == ',');
}

void Tictactoe::pve() {
    m_player = 'X';
    m_env = '0';
    int x, y;
    char s;

    system(CLEAR);
    printf("Enter coordinates as x,y. For stop enter -1\n");
    print_field();
    do {
        s = '.';
        printf("%c move: ", m_player);
        scanf("%i", &x);
        if (x == -1) {
            printf("Interrupt\n");
            break;
        }
        scanf("%c%i", &s, &y);
        if (m_first_move == Place::NONE) {
            // remember first player move
            m_first_move = check_place(x, y);
            m_firstx = x;
            m_firsty = y;
        }
        m_move = check_place(x, y);
        if (fill_point(x, y, m_player)) {
            system(CLEAR);

            inc_filled();
            printf("Player move:\n");
            print_field();
            if (win()) {
                break;
            }
            env_move(x, y);
            printf("Env move:\n");
            print_field();
            inc_filled();
            if (win()) {
                break;
            }
        } else {
            printf("Incorrect. Try again\n");
        }
    } while(s == ',');
}

void Tictactoe::play() {
    int mode;
    do {
        init();
        printf("Choose mode (1 - pve, 2 - pvp, -1 for exit): ");
        scanf("%i", &mode);
        if (mode == 1) {
            pve();
        } else if (mode == 2) {
            pvp();
        } else {
            printf("Incorrect\n");
        }
    } while(mode != -1);
}
