#include <stdio.h>
#include <stdbool.h>

#define SIZE 8

void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool isValidMove(char board[SIZE][SIZE], int x1, int y1, int x2, int y2, char player) {
    if (x2 < 0 || x2 >= SIZE || y2 < 0 || y2 >= SIZE) return false;
    if (board[x2][y2] != '.') return false;
    if (player == 'x' && x2 == x1 + 1 && (y2 == y1 - 1 || y2 == y1 + 1)) return true;
    if (player == 'o' && x2 == x1 - 1 && (y2 == y1 - 1 || y2 == y1 + 1)) return true;
    if (player == 'x' && x2 == x1 + 2 && (y2 == y1 - 2 || y2 == y1 + 2) && board[(x1 + x2) / 2][(y1 + y2) / 2] == 'o') return true;
    if (player == 'o' && x2 == x1 - 2 && (y2 == y1 - 2 || y2 == y1 + 2) && board[(x1 + x2) / 2][(y1 + y2) / 2] == 'x') return true;
    return false;
}

void makeMove(char board[SIZE][SIZE], int x1, int y1, int x2, int y2, char player) {
    board[x2][y2] = player;
    board[x1][y1] = '.';
    if (abs(x2 - x1) == 2) {
        board[(x1 + x2) / 2][(y1 + y2) / 2] = '.';
    }
}

bool hasMoves(char board[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == player) {
                for (int dx = -2; dx <= 2; dx++) {
                    for (int dy = -2; dy <= 2; dy++) {
                        if (isValidMove(board, i, j, i + dx, j + dy, player)) return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    char board[SIZE][SIZE] = {
        {'.', 'x', '.', 'x', '.', 'x', '.', 'x'},
        {'x', '.', 'x', '.', 'x', '.', 'x', '.'},
        {'.', 'x', '.', 'x', '.', 'x', '.', 'x'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'o', '.', 'o', '.', 'o', '.', 'o', '.'},
        {'.', 'o', '.', 'o', '.', 'o', '.', 'o'},
        {'o', '.', 'o', '.', 'o', '.', 'o', '.'}
    };
    char currentPlayer = 'x';
    while (hasMoves(board, 'x') && hasMoves(board, 'o')) {
        printBoard(board);
        int x1, y1, x2, y2;
        printf("Player %c, enter your move (x1 y1 x2 y2): ", currentPlayer);
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (isValidMove(board, x1, y1, x2, y2, currentPlayer)) {
            makeMove(board, x1, y1, x2, y2, currentPlayer);
            currentPlayer = (currentPlayer == 'x') ? 'o' : 'x';
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
    printBoard(board);
    if (!hasMoves(board, 'o')) {
        printf("Player x wins!\n");
    } else {
        printf("Player o wins!\n");
    }
    return 0;
}
