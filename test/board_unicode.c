#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define SIZE 8
#define BLACK L'⚫'
#define WHITE L'⚪'

void initializeBoard(wchar_t board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = L'　';
        }
    }
    board[3][3] = board[4][4] = BLACK;
    board[3][4] = board[4][3] = WHITE;
}

void printBoard(wchar_t board[SIZE][SIZE]) {
    wprintf(L"  ａｂｃｄｅｆｇｈ\n"); //全角アルファベット
    for (int i = 0; i < SIZE; i++) {
        wprintf(L"%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            wprintf(L"%lc", board[i][j]);
        }
        wprintf(L"\n");
    }
}

int main() {
    setlocale(LC_ALL, "");
    wchar_t board[SIZE][SIZE];
    initializeBoard(board);
    printBoard(board);
    return 0;
}
