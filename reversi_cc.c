// Reversi Simulation
// Computer vs Computer random play

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 8
#define EMPTY 0
#define BLACK 1
#define WHITE 2

int board[SIZE][SIZE];

// Structure to represent a move
typedef struct {
    int row;
    int col;
    int player;
} Move;

// Function prototypes
void initializeBoard();
void printBoard();
int checkDirection(int row, int col, int player, int dx, int dy);
void flipDisks(int row, int col, int player);
int getValidMoves(int player, Move validMoves[SIZE * SIZE]);
Move getRandomMove(Move validMoves[SIZE * SIZE], int count);
int playComputerTurn(int player);
void displayGameResult();

int main() {
    srand(time(NULL));  // Initialize random seed

    char board[SIZE][SIZE];
    initializeBoard();
    printBoard();

    int player = BLACK;
    int moves = 2;
    int active_players = 2;

    // Main game loop
    while (1) {
        if (!playComputerTurn(player)) {
            active_players -= 1;
            printBoard();
            if (active_players == 1) {
                printf("%d has no valid moves. Passing turn.\n", player);
                usleep(300000);
            } else if (active_players == 0) {
                printf("Neither player can move. Game over.\n");
                usleep(300000);
                break;
            }
        } else {
            active_players = 2;
        }
        player = (player == BLACK) ? WHITE : BLACK;  // Switch players
    }

    displayGameResult();
    return 0;
}

// Initialize the game board
void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    // Set up initial positions
    board[3][3] = board[4][4] = WHITE;
    board[3][4] = board[4][3] = BLACK;
}

// Display the current state of the board
void printBoard() {
    printf("\e[1;1H\e[2J");        // Clear screen
    printf("  a b c d e f g h\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if a move is valid in a specific direction
int checkDirection(int row, int col, int player, int dx, int dy) {
    int x = row + dx;
    int y = col + dy;
    int count = 0;

    while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] != EMPTY && board[x][y] != player) {
        x += dx;
        y += dy;
        count++;
    }

    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == player && count > 0) {
        return count;
    }
    return 0;
}

// Flip disks after a valid move
void flipDisks(int row, int col, int player) {
    int directions[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    int x = row;
    int y = col;

    for (int i = 0; i < SIZE; i++) {
        int dx = directions[i][0];
        int dy = directions[i][1];
        int count = checkDirection(row, col, player, dx, dy);
        if (count) {
            for (int i = 0; i <= count; i++) {
                board[x][y] = player;
                printBoard();
                x += dx;
                y += dy;
                usleep(100000);  // Add delay for visual effect
            }
        }
    }
}

// Check if a move is valid
int isValidMove(int row, int col, int player) {
    if (board[row][col] != EMPTY) return 0;

    int directions[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (int i = 0; i < SIZE; i++) {
        if (checkDirection(row, col, player, directions[i][0], directions[i][1])) {
            return 1;
        }
    }
    return 0;
}

// Get a random valid move
Move getRandomMove(Move validMoves[SIZE * SIZE], int count) {
    srand(time(NULL)); // Initialize random seed
    int index = rand() % count;
    return validMoves[index];
}

// Play a computer turn
int playComputerTurn(int player) {
    printf("Computer %d's turn.\n", player);
    usleep(300000);
    Move validMoves[SIZE * SIZE];
    int moveCount = 0;
    // Find all valid moves
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (isValidMove(i, j, player)) {
                validMoves[moveCount].row = i;
                validMoves[moveCount].col = j;
                moveCount++;
            }
        }
    }
    if (moveCount > 0) {
        Move move = getRandomMove(validMoves, moveCount);
        flipDisks(move.row, move.col, player);
        return 1;
    } else {
        return 0;  // No valid moves
    }
}

// Display the final game result
void displayGameResult() {
    printBoard();
    int blackCount = 0, whiteCount = 0;
    // Count disks
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == BLACK) blackCount++;
            if (board[i][j] == WHITE) whiteCount++;
        }
    }
    printf("Game over. Black: %d, White: %d\n", blackCount, whiteCount);
    // Determine winner
    if (blackCount > whiteCount) {
        printf("Black wins!\n");
    } else if (whiteCount > blackCount) {
        printf("White wins!\n");
    } else {
        printf("It's a tie!\n");
    }
}
