#include <stdio.h>

#define SIZE 8

// isValidMove と isValidMove の一部をまとめて
// checkDirection関数を追加したパターン
// それにボードを上書きする関数追加

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    board[3][3] = board[4][4] = 'W'; // White
    board[3][4] = board[4][3] = 'B'; // Black
}

void clearScreen() {
    printf("\e[1;1H\e[2J");
}

void printBoard(char board[SIZE][SIZE]) {
    clearScreen();
    printf("  a b c d e f g h\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int checkDirection(char board[SIZE][SIZE], int row, int col, char player, int dx, int dy, int flip) {
    int x = row + dx;
    int y = col + dy;
    int count = 0;

    while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] != ' ' && board[x][y] != player) {
        x += dx;
        y += dy;
        count++;
    }

    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == player && count > 0) {
        if (flip) {
            for (int i = 0; i <= count; i++) {
                x -= dx;
                y -= dy;
                board[x][y] = player;
            }
        }
        return 1;
    }
    return 0;
}

int isValidMove(char board[SIZE][SIZE], int row, int col, char player) {
    if (board[row][col] != ' ') return 0;

    int directions[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (int i = 0; i < 8; i++) {
        if (checkDirection(board, row, col, player, directions[i][0], directions[i][1], 0)) {
            return 1;
        }
    }
    return 0;
}

void flipDisks(char board[SIZE][SIZE], int row, int col, char player) {
    int directions[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (int i = 0; i < 8; i++) {
        checkDirection(board, row, col, player, directions[i][0], directions[i][1], 1);
    }
}

int main() {
    char board[SIZE][SIZE];
    initializeBoard(board);

    char player = 'B'; // Black starts
    int row, col;
    char colChar;

    while (1) {
        printBoard(board);
        printf("%c's turn. Enter move (e.g., e6): ", player);
        scanf(" %c%d", &colChar, &row);
        col = colChar - 'a';
        row -= 1;

        if (isValidMove(board, row, col, player)) {
            flipDisks(board, row, col, player);
            player = (player == 'B') ? 'W' : 'B';
        } else {
            printf("Invalid move. Try again.\n");
        }

        // 終了判定
        // TODO: すべての合法な手をチェックして、ゲーム終了かどうかを確認する
    }

    return 0;
}

