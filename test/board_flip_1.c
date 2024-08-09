#include <stdio.h>

#define SIZE 8

// 関数`flipDisks`と`isValidMove`で重複するコードも多いがそのままで

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    board[3][3] = board[4][4] = 'W'; // White
    board[3][4] = board[4][3] = 'B'; // Black
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
    printf("\n");
}

void flipDisks(char board[SIZE][SIZE], int row, int col, char player) {
    // 8方向を確認
    int directions[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (int i = 0; i < 8; i++) {
        int x = row + directions[i][0];
        int y = col + directions[i][1];
        int count = 0;

        // 相手の駒を探す
        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] != ' ' && board[x][y] != player) {
            x += directions[i][0];
            y += directions[i][1];
            count++;
        }

        // 自分の駒で挟まれている場合
        if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == player) {
            for (int j = 0; j <= count; j++) {
                x -= directions[i][0];
                y -= directions[i][1];
                board[x][y] = player;
            }
        }
    }
}

int isValidMove(char board[SIZE][SIZE], int row, int col, char player) {
    if (board[row][col] != ' ') return 0;

    // 8方向を確認
    int directions[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (int i = 0; i < 8; i++) {
        int x = row + directions[i][0];
        int y = col + directions[i][1];
        int count = 0;

        // 相手の駒を探す
        while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] != ' ' && board[x][y] != player) {
            x += directions[i][0];
            y += directions[i][1];
            count++;
        }

        // 自分の駒で挟まれている場合
        if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == player && count > 0) {
            return 1;
        }
    }
    return 0;
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

