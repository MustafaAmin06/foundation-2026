# Reversi (Othello) — `reversi.c`

## What is Reversi?

Reversi (also sold as **Othello**) is a classic two-player strategy board game
played on an 8×8 grid.  Each disc has a black side and a white side.  Players
fight for board control by **sandwiching** and **flipping** their opponent's
discs.

---

## How to compile and run

```bash
gcc -Wall -Wextra -o reversi reversi.c
./reversi
```

When prompted, enter the **row** and **column** (both 1–8) of the cell where
you want to place your disc, separated by a space.

```
Black's turn (X): enter row col: 3 4
```

---

## Rules

| Concept | Detail |
|---------|--------|
| Board | 8×8 grid, starts with 2 Black (X) and 2 White (O) discs in the centre |
| Turn order | Black moves first |
| Legal move | You must place your disc so that at least one straight line (horizontal, vertical, or diagonal) is formed where your disc is at one end, your opponent's disc(s) are in the middle, and another of your discs is at the other end |
| Flipping | Every opponent disc sandwiched in such a line is flipped to your colour |
| Passing | If a player has no legal move, their turn is skipped |
| Game over | When **neither** player has a legal move (board is full or completely locked) |
| Winner | Player with the most discs on the board wins |

---

## How the code works

### Data representation

```c
#define EMPTY 0
#define BLACK 1   // X
#define WHITE 2   // O

int board[SIZE][SIZE];   // 8×8 integer array
```

Each cell stores `EMPTY`, `BLACK`, or `WHITE`.

### Key functions

| Function | Purpose |
|----------|---------|
| `initBoard` | Sets up the 8×8 array with the 4 starting discs |
| `printBoard` | Renders the board to the terminal with row/column labels |
| `checkAndFlip` | Core logic — walks all 8 directions from a cell, counts sandwiched opponent discs, and (optionally) flips them |
| `isLegalMove` | Calls `checkAndFlip` in *check-only* mode (no flipping) |
| `applyMove` | Places the disc and calls `checkAndFlip` in *flip* mode |
| `hasLegalMove` | Scans every empty cell to decide if a player has at least one valid move |
| `countDiscs` | Tallies Black and White discs for the score display |

### Direction table

All 8 straight-line directions are encoded as row-delta / column-delta pairs:

```c
static const int DR[] = {-1, -1, -1,  0,  0,  1,  1,  1};
static const int DC[] = {-1,  0,  1, -1,  1, -1,  0,  1};
```

`checkAndFlip` iterates over all 8 entries to cover every possible sandwich.

### Game loop

```
while (passCount < 2):
    if current player has no legal move → pass (passCount++)
    else → read input, validate, apply move, switch player, reset passCount
```

Two consecutive passes means neither player can move, so the game ends.

---

## Example output

```
    1 2 3 4 5 6 7 8
   +----------------
 1 | . . . . . . . .
 2 | . . . . . . . .
 3 | . . . . . . . .
 4 | . . . O X . . .
 5 | . . . X O . . .
 6 | . . . . . . . .
 7 | . . . . . . . .
 8 | . . . . . . . .

  Score  X:2  O:2
  Black's turn (X): enter row col: 3 4
```

Placing Black at row 3, col 4 sandwiches the White disc at (4,4) diagonally,
so it is flipped to Black.

---

## Concepts practiced

- **2D arrays** — the entire board is an `int[8][8]`
- **Direction vectors** — a clean way to search all 8 directions without
  duplicating code
- **Game state management** — tracking whose turn it is, detecting pass/end
  conditions, and keeping score
- **Input validation** — bounds checking and legality checking before applying
  any move
