#include <stdio.h>

#define SIZE 8
#define BLACK 'B'
#define WHITE 'W'

// 単に初期ボードを描画するだけのコード

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    board[3][3] = board[4][4] = BLACK;
    board[3][4] = board[4][3] = WHITE;
}

void printBoard(char board[SIZE][SIZE]) {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char board[SIZE][SIZE];
    initializeBoard(board);
    printBoard(board);
    return 0;
}
