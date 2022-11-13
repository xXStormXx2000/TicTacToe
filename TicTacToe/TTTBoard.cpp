#include "TTTBoard.h"

bool TTTBoard::checkPosition(int x, int y) {
    int pos = 0, ofset = 0, pos1 = 0, ofset1 = 0;
    if (y == 0) ofset1 = 3;
    if (y == 1) {
        ofset = 5;
        pos1 = 1;
    }
    if (y == 2) {
        ofset = 2;
        pos = 1;
        pos1 = 1;
        ofset1 = 5;
    }
    if ((board[pos] >> ofset & 7) == 1 && (board[pos1] >> ofset1 & 3) == 2) return false;
    if (!(board[pos] >> ofset & 7) && (board[pos1] >> ofset1 & 3)) return false;
    if (board[pos] >> ofset + x & 1) return false;
    return true;
}

void TTTBoard::updateBoard(int x, int y, bool o) {
    if (1 > x || x > 3 || 1 > y || y > 3) throw (std::string)"You must write two numbers from 1 to 3.";
    x--;
    y--;
    if (!checkPosition(x, y)) throw (std::string)"The position you have selected is already occupied.";
    int pos = 0, ofset = 0, pos1 = 0, ofset1 = 0;
    if (y == 0) ofset1 = 3;
    if (y == 1) {
        ofset = 5;
        pos1 = 1;
    }
    if (y == 2) {
        ofset = 2;
        pos = 1;
        pos1 = 1;
        ofset1 = 5;
    }
    board[pos] |= 1 << x + ofset;
    int n = 0, m = 0;
    for (int i = 0; i < 3; i++) if (board[pos] >> (i + ofset) & 1) {
        if (i < x) m++;
        n++;
    }
    if (n == 3) {
        if (x == 0 && o) return;
        m--;
        bool temp = board[pos1] >> ofset1 & 1;
        board[pos1] &= ~(1 << ofset1);
        if (m) {
            board[pos1] |= (board[pos1] >> ofset1 + 1 & 1) << ofset1;
            board[pos1] &= ~(1 << (ofset1 + 1));
        }
        board[pos1] |= o << (ofset1 + m);
        if (temp) return;
        board[pos] &= ~(7 << ofset);
        if (!(board[pos1] >> ofset1 & 3)) {
            board[pos] |= 1 << ofset;
            board[pos1] |= 2 << ofset1;
        }
    }
    else {
        if (!m && n == 2) {
            board[pos1] &= ~(1 << ofset1 + 1);
            board[pos1] |= (board[pos1] >> ofset1 & 1) << ofset1 + 1;
        }
        board[pos1] &= ~(1 << ofset1 + m);
        board[pos1] |= o << (ofset1 + m);
    }
}

char TTTBoard::threeInARow() {
    std::vector<std::vector<char>> a(3, std::vector<char>(3,0));
    for (int i = 0; i < 3; i++) {
        int pos = 0, ofset = 0, pos1 = 0, ofset1 = 0;
        if (i == 0) ofset1 = 3;
        if (i == 1) {
            ofset = 5;
            pos1 = 1;
        }
        if (i == 2) {
            ofset = 2;
            pos = 1;
            pos1 = 1;
            ofset1 = 5;
        }
        if ((board[pos] >> ofset & 7) == 1 && (board[pos1] >> ofset1 & 3) == 2) return 'O';
        if ((board[pos] >> ofset & 7) == 7 && (board[pos1] >> ofset1 & 3) == 3) return 'X';
        if (!(board[pos] >> ofset & 7) && (board[pos1] >> ofset1 & 3)) {
            a[0][i] = 'O';
            for (int j = 0; j < 2; j++) {
                if (board[pos1] >> ofset1 + j & 1) {
                    a[j + 1][i] = 'X';
                }
                else {
                    a[j + 1][i] = 'O';
                }
            }
            continue;
        }
        int temp = 0, n = 0;
        for (int j = 0; j < 3; j++) if (board[pos] >> (ofset + j) & 1) n++;
        if (n == 3) a[0][i] = 'X';
        for (int j = 0; j < 3 - (n == 3); j++) {
            if(board[pos] >> ofset + j & 1) {
                if (board[pos1] >> ofset1 + temp & 1) {
                    a[j + (n == 3)][i] = 'X';
                }
                else {
                    a[j + (n == 3)][i] = 'O';
                }
                temp++;
            }
        }
        std::cout << "\n";
    }
    for (auto i : a) {
        if (i[0] && i[0] == i[1] && i[1] == i[2]) return i[0];
    }
    if (a[0][0] && a[0][0] == a[1][1] && a[1][1] == a[2][2]) return a[0][0];
    if (a[2][0] && a[2][0] == a[1][1] && a[1][1] == a[0][2]) return a[2][0];
    for (auto i : a) for (char j : i) if (j == 0) return 0;
    return 'D';
}

void TTTBoard::drawBoard() {
    for (int i = 0; i < 3; i++) {
        int pos = 0, ofset = 0, pos1 = 0, ofset1 = 0;
        if (i == 0) ofset1 = 3;
        if (i == 1) {
            ofset = 5;
            pos1 = 1;
        }
        if (i == 2) {
            ofset = 2;
            pos = 1;
            pos1 = 1;
            ofset1 = 5;
        }
        if ((board[pos] >> ofset & 7) == 1 && (board[pos1] >> ofset1 & 3) == 2) {
            std::cout << "| O | O | O |\n";
            continue;
        }
        std::cout << "|";
        if (!(board[pos] >> ofset & 7) && (board[pos1] >> ofset1 & 3)) {
            std::cout << " O |";
            for (int j = 0; j < 2; j++) {
                if (board[pos1] >> ofset1 + j & 1) {
                    std::cout << " X |";
                }
                else {
                    std::cout << " O |";
                }
            }
            std::cout << "\n";
            continue;
        }
        int temp = 0, n = 0;
        for (int j = 0; j < 3; j++) if (board[pos] >> (ofset + j) & 1) n++;
        if(n == 3) std::cout << " X |";
        for (int j = 0; j < 3 - (n == 3); j++) {
            if (!(board[pos] >> ofset + j & 1)) {
                std::cout << "   |";
            } else {
                if (board[pos1] >> ofset1 + temp & 1) {
                    std::cout << " X |";
                } else {
                    std::cout << " O |";
                }
                temp++;
            }
        }
        std::cout << "\n";
    }
}
