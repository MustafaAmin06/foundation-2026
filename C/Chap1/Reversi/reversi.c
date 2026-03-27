// Reversi (Othello) game in C
// Two players take turns placing discs on an 8x8 board.
// When a disc is placed, all opponent discs sandwiched in a straight line
// (horizontal, vertical, or diagonal) between the new disc and another
// friendly disc are flipped to the current player's colour.
// The game ends when neither player has a legal move.
// The player with the most discs wins.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 8
#define EMPTY 0
#define BLACK 1   // player 1
#define WHITE 2   // player 2

// Directions: 8 possible straight lines from any cell
static const int DR[] = {-1, -1, -1,  0,  0,  1,  1,  1};
static const int DC[] = {-1,  0,  1, -1,  1, -1,  0,  1};

// ── Board helpers ─────────────────────────────────────────────────────────────

void initBoard(int board[SIZE][SIZE]) {
    memset(board, EMPTY, sizeof(int) * SIZE * SIZE);
    // Standard Reversi starting position
    board[3][3] = WHITE;
    board[3][4] = BLACK;
    board[4][3] = BLACK;
    board[4][4] = WHITE;
}

void printBoard(int board[SIZE][SIZE]) {
    printf("\n    ");
    for (int c = 0; c < SIZE; c++) printf("%d ", c + 1);
    printf("\n   +");
    for (int c = 0; c < SIZE; c++) printf("--");
    printf("\n");
    for (int r = 0; r < SIZE; r++) {
        printf(" %d | ", r + 1);
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c] == BLACK)       printf("X ");
            else if (board[r][c] == WHITE)  printf("O ");
            else                            printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

// ── Game logic ────────────────────────────────────────────────────────────────

// Returns the opponent's colour
int opponent(int player) {
    return (player == BLACK) ? WHITE : BLACK;
}

// Checks whether placing `player`'s disc at (row, col) is a legal move.
// If `flip` is true, it also flips the sandwiched discs.
bool checkAndFlip(int board[SIZE][SIZE], int row, int col, int player, bool flip) {
    if (board[row][col] != EMPTY) return false;

    int opp = opponent(player);
    bool legal = false;

    for (int d = 0; d < 8; d++) {
        int r = row + DR[d];
        int c = col + DC[d];
        int count = 0;

        // Walk while we see opponent discs
        while (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == opp) {
            r += DR[d];
            c += DC[d];
            count++;
        }

        // Legal if we end on a friendly disc and sandwiched at least one opponent disc
        if (count > 0 && r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == player) {
            legal = true;
            if (flip) {
                // Walk back and flip
                int fr = row + DR[d];
                int fc = col + DC[d];
                while (fr != r || fc != c) {
                    board[fr][fc] = player;
                    fr += DR[d];
                    fc += DC[d];
                }
            }
        }
    }
    return legal;
}

bool isLegalMove(int board[SIZE][SIZE], int row, int col, int player) {
    return checkAndFlip(board, row, col, player, false);
}

void applyMove(int board[SIZE][SIZE], int row, int col, int player) {
    board[row][col] = player;
    checkAndFlip(board, row, col, player, true);
}

// Returns true if `player` has at least one legal move
bool hasLegalMove(int board[SIZE][SIZE], int player) {
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            if (isLegalMove(board, r, c, player)) return true;
    return false;
}

// Count discs for each player
void countDiscs(int board[SIZE][SIZE], int *blackCount, int *whiteCount) {
    *blackCount = 0;
    *whiteCount = 0;
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c] == BLACK) (*blackCount)++;
            else if (board[r][c] == WHITE) (*whiteCount)++;
        }
}

// ── Main game loop ─────────────────────────────────────────────────────────────

int main(void) {
    int board[SIZE][SIZE];
    initBoard(board);

    int current = BLACK;   // Black moves first in standard Reversi
    int passCount = 0;     // Two consecutive passes → game over

    printf("Reversi (Othello)\n");
    printf("  X = Black (Player 1)   O = White (Player 2)\n");
    printf("  Enter row and column (1-8) to place your disc.\n");

    while (passCount < 2) {
        printBoard(board);

        int black, white;
        countDiscs(board, &black, &white);
        printf("  Score  X:%d  O:%d\n", black, white);

        if (!hasLegalMove(board, current)) {
            printf("  %s has no legal moves — passing.\n\n",
                   current == BLACK ? "Black (X)" : "White (O)");
            current = opponent(current);
            passCount++;
            continue;
        }
        passCount = 0;

        printf("  %s's turn (%s): enter row col: ",
               current == BLACK ? "Black" : "White",
               current == BLACK ? "X" : "O");

        int row, col;
        if (scanf("%d %d", &row, &col) != 2) {
            printf("  Invalid input. Try again.\n");
            // flush remaining input until newline
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;  // discard characters
            continue;
        }
        row--;  // convert 1-indexed to 0-indexed
        col--;

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("  Out of range. Try again.\n");
            continue;
        }

        if (!isLegalMove(board, row, col, current)) {
            printf("  Illegal move. Try again.\n");
            continue;
        }

        applyMove(board, row, col, current);
        current = opponent(current);
    }

    // Final result
    printBoard(board);
    int black, white;
    countDiscs(board, &black, &white);
    printf("  Game over!\n");
    printf("  Final score  X:%d  O:%d\n", black, white);
    if (black > white)       printf("  Black (X) wins!\n");
    else if (white > black)  printf("  White (O) wins!\n");
    else                     printf("  It's a draw!\n");

    return 0;
}
