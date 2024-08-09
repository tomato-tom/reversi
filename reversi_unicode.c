#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define SIZE 8
#define EMPTY 0
#define BLACK 1
#define WHITE 2

typedef enum {
    HUMAN_VS_HUMAN,
    HUMAN_VS_COMPUTER,
    COMPUTER_VS_COMPUTER
} GameMode;

typedef struct {
    int row;
    int col;
    int player;
} Move;

// グローバル変数
int board[SIZE][SIZE];

// 関数プロトタイプ
void initializeBoard();
void printBoard();
int checkDirection(int row, int col, int player, int dx, int dy, int flip);
int isValidMove(int row, int col, int player);
int hasValidMove(int player);
void flipDisks(int row, int col, int player);
int getValidMoves(int player, Move validMoves[SIZE * SIZE]);
Move getRandomMove(Move validMoves[SIZE * SIZE], int count);
GameMode parseArguments(int argc, char *argv[]);
void playHumanTurn(int player);
void playComputerTurn(int player);
void displayGameResult();

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    initializeBoard();
    printBoard();

    GameMode gameMode = parseArguments(argc, argv);

    int player = BLACK;
    int humanPlayer = BLACK;

    if (gameMode == HUMAN_VS_COMPUTER) {
        humanPlayer = (rand() % 2) == 0 ? BLACK : WHITE;
        char* color = (humanPlayer == BLACK) ? "Black" : "White";
        printf("Human player: %s\n", color);
        printf("Computer player: %s\n", (humanPlayer == BLACK) ? "White" : "Black");
    }

    while (1) {
        if (!hasValidMove(player)) {
            printBoard();
            char* color = (player == BLACK) ? "Black" : "White";
            printf("%s has no valid moves. Passing turn.\n", color);
            player = (player == BLACK) ? WHITE : BLACK;
            sleep(1);
            if (!hasValidMove(player)) {
                printBoard();
                printf("Neither player can move. Game over.\n");
                sleep(1);
                break;
            }
            continue;
        }

        switch (gameMode) {
            case HUMAN_VS_HUMAN:
                playHumanTurn(player);
                break;
            case HUMAN_VS_COMPUTER:
                if (player == humanPlayer) {
                    playHumanTurn(player);
                } else {
                    playComputerTurn(player);
                }
                break;
            case COMPUTER_VS_COMPUTER:
                playComputerTurn(player);
                break;
        }

        player = (player == BLACK) ? WHITE : BLACK;
    }

    displayGameResult();
    return 0;
}


void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    board[3][3] = board[4][4] = WHITE;
    board[3][4] = board[4][3] = BLACK;
}

void printBoard() {
    printf("\e[1;1H\e[2J");        // clear board 
    printf("  ａｂｃｄｅｆｇｈ\n"); //全角アルファベット
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            switch (board[i][j]) {
                case EMPTY:
                    printf("\x1b[42m　\x1b[49m"); break;
                case BLACK:
                    printf("\x1b[42m⚫\x1b[49m"); break;
                case WHITE:
                    printf("\x1b[42m⚪\x1b[49m"); break;
            }
        }
        printf("\n");
    }
    printf("\n");
}


int checkDirection(int row, int col, int player, int dx, int dy, int flip) {
    int x = row + dx;
    int y = col + dy;
    int count = 0;

    while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] != EMPTY && board[x][y] != player) {
        x += dx;
        y += dy;
        count++;
    }

    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == player && count > 0) {
        if (flip) {
            x = row;
            y = col;
            for (int i = 0; i <= count; i++) {
                board[x][y] = player;
                printBoard();
                x += dx;
                y += dy;
                usleep(100000);
            }
        }
        return 1;
    }
    return 0;
}

int isValidMove(int row, int col, int player) {
    if (board[row][col] != EMPTY) return 0;

    int directions[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (int i = 0; i < SIZE; i++) {
        if (checkDirection(row, col, player, directions[i][0], directions[i][1], 0)) {
            return 1;
        }
    }
    return 0;
}

int hasValidMove(int player) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (isValidMove(i, j, player)) {
                return 1;
            }
        }
    }
    return 0;
}

void flipDisks(int row, int col, int player) {
    int directions[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (int i = 0; i < SIZE; i++) {
        checkDirection(row, col, player, directions[i][0], directions[i][1], 1);
    }
}

int getValidMoves(int player, Move validMoves[SIZE * SIZE]) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (isValidMove(i, j, player)) {
                validMoves[count].row = i;
                validMoves[count].col = j;
                count++;
            }
        }
    }
    return count;
}

Move getRandomMove(Move validMoves[SIZE * SIZE], int count) {
    srand(time(NULL)); // シードを初期化
    int index = rand() % count;
    return validMoves[index];
}

GameMode parseArguments(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "human-vs-computer") == 0 || strcmp(argv[1], "hc") == 0) {
            return HUMAN_VS_COMPUTER;
        } else if (strcmp(argv[1], "computer-vs-computer") == 0 || strcmp(argv[1], "cc") == 0) {
            return COMPUTER_VS_COMPUTER;
        }
    }
    return HUMAN_VS_HUMAN;
}

void playHumanTurn(int player) {
    int row, col;
    char colChar;

    while (1) {
        char* color = (player == BLACK) ? "Black" : "White";
        printf("%s's turn. Enter move (e.g., e6): ", color);
        scanf(" %c%d", &colChar, &row);
        col = colChar - 'a';
        row -= 1;

        if (isValidMove(row, col, player)) {
            flipDisks(row, col, player);
            break;
        } else {
            printBoard();
            printf("Invalid move. Try again.\n");
            sleep(1);
        }
    }
}

void playComputerTurn(int player) {
    char* color = (player == BLACK) ? "Black" : "White";
    printf("Computer %s's turn.\n", color);
    usleep(300000);
    Move validMoves[SIZE * SIZE];
    int moveCount = getValidMoves(player, validMoves);
    if (moveCount > 0) {
        Move move = getRandomMove(validMoves, moveCount);
        flipDisks(move.row, move.col, player);
    }
}

void displayGameResult() {
    printBoard();
    int blackCount = 0, whiteCount = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == BLACK) blackCount++;
            if (board[i][j] == WHITE) whiteCount++;
        }
    }
    printf("Game over. Black: %d, White: %d\n", blackCount, whiteCount);
    if (blackCount > whiteCount) {
        printf("Black wins!\n");
    } else if (whiteCount > blackCount) {
        printf("White wins!\n");
    } else {
        printf("It's a tie!\n");
    }
}

