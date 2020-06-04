#include <iostream>
#include "map.h"
using namespace std;

int main() {
    Map map;
    int x, y;
    char s, player = 'X';
    cout << "Enter coordinates as 1,2. For stop enter -1\n";
    map.print_field();
    do {
        s = '.';// disable infinity loop when tap ctrl+d
        cout << player << " move: ";
        cin >> x;
        if (x == -1) {
            cout << "exit\n";
            break;
        }
        cin >> s >> y;
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