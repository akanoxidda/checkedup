#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]);
int isValidMove(int fromX, int fromY, int toX, int toY, char board[BOARD_SIZE][BOARD_SIZE], char player);
int makeMove(int fromX, int fromY, int toX, int toY, char board[BOARD_SIZE][BOARD_SIZE], char player);
void playerMove(char board[BOARD_SIZE][BOARD_SIZE]);
void computerMove(char board[BOARD_SIZE][BOARD_SIZE]);

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    int gameOver = 0;
    
    initializeBoard(board);
    srand(time(NULL));

    while (!gameOver) {
        printBoard(board);
        playerMove(board);
        computerMove(board);
    }

    printf("Game over!\n");
    return 0;
}

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    int i, j;

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if ((i + j) % 2 == 0) {
                board[i][j] = ' ';
            } else {
                if (i < 3) {
                    board[i][j] = 'X';
                } else if (i > 4) {
                    board[i][j] = 'O';
                } else {
                    board[i][j] = ' ';
                }
            }
        }
    }
}

void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    int i, j;
    printf("\n  1 2 3 4 5 6 7 8\n");
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i + 1);
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int isValidMove(int fromX, int fromY, int toX, int toY, char board[BOARD_SIZE][BOARD_SIZE], char player) {
    if (toX < 0 || toX >= BOARD_SIZE || toY < 0 || toY >= BOARD_SIZE) {
        return 0;
    }
    if (board[toX][toY] != ' ') {
        return 0;
    }
    if (abs(fromX - toX) != 1 || abs(fromY - toY) != 1) {
        return 0;
    }
    if (player == 'O' && board[fromX][fromY] != 'O') {
        return 0;
    }
    if (player == 'X' && board[fromX][fromY] != 'X') {
        return 0;
    }
    return 1;
}

int makeMove(int fromX, int fromY, int toX, int toY, char board[BOARD_SIZE][BOARD_SIZE], char player) {
    if (isValidMove(fromX, fromY, toX, toY, board, player)) {
        board[toX][toY] = board[fromX][fromY];
        board[fromX][fromY] = ' ';
        return 1;
    }
    return 0;
}

void playerMove(char board[BOARD_SIZE][BOARD_SIZE]) {
    int fromX, fromY, toX, toY;
    int valid = 0;
    
    while (!valid) {
        printf("Enter your move (fromX fromY toX toY): ");
        scanf("%d %d %d %d", &fromX, &fromY, &toX, &toY);
        fromX--; fromY--; toX--; toY--;
        valid = makeMove(fromX, fromY, toX, toY, board, 'O');
        if (!valid) {
            printf("Invalid move, try again.\n");
        }
    }
}

void computerMove(char board[BOARD_SIZE][BOARD_SIZE]) {
    int fromX, fromY, toX, toY;
    int valid = 0;

    while (!valid) {
        fromX = rand() % BOARD_SIZE;
        fromY = rand() % BOARD_SIZE;
        toX = fromX + (rand() % 2 == 0 ? 1 : -1);
        toY = fromY + (rand() % 2 == 0 ? 1 : -1);
        valid = makeMove(fromX, fromY, toX, toY, board, 'X');
    }

    printf("Computer moves from (%d,%d) to (%d,%d)\n", fromX + 1, fromY + 1, toX + 1, toY + 1);
}
