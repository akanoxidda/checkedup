#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 8

char board[SIZE][SIZE];

void initBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((i + j) % 2 == 1 && i < 3) board[i][j] = 'x';
            else if ((i + j) % 2 == 1 && i > 4) board[i][j] = 'o';
            else board[i][j] = '.';
        }
    }
}

void displayBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

bool isValidMove(int x1, int y1, int x2, int y2, char player) {
    if (x2 < 0 || x2 >= SIZE || y2 < 0 || y2 >= SIZE || board[x2][y2] != '.') return false;
    if (player == 'x' && x2 == x1 + 1 && abs(y2 - y1) == 1) return true;
    if (player == 'o' && x2 == x1 - 1 && abs(y2 - y1) == 1) return true;
    return false;
}

void makeMove(int x1, int y1, int x2, int y2) {
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = '.';
}

int main() {
    int x1, y1, x2, y2;
    char currentPlayer = 'x';
    initBoard();
    while (1) {
        displayBoard();
        printf("Player %c, enter your move (x1 y1 x2 y2): ", currentPlayer);
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (isValidMove(x1, y1, x2, y2, currentPlayer)) {
            makeMove(x1, y1, x2, y2);
            currentPlayer = (currentPlayer == 'x') ? 'o' : 'x';
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
    return 0;
}
