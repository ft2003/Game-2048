#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define SIZE 4

void init_board(int board[SIZE][SIZE]);
void generate_random_tile(int board[SIZE][SIZE]);
void draw_board(int board[SIZE][SIZE]);
void move(char ch, int board[SIZE][SIZE]);
int check_game_over(int board[SIZE][SIZE]);
void game_over();

int main() {
    int board[SIZE][SIZE];
    int score = 0;
    char ch;

    srand(time(0)); // seed the random number generator

    // initialize ncurses library
    initscr();
    cbreak();
    noecho();

    // initialize the game board
    init_board(board);
    generate_random_tile(board);
    generate_random_tile(board);
    draw_board(board);

    // main game loop
    while (1) {
        ch = getch();
        if (ch == 'q') {
            break;
        }
        move(ch, board);
        if (check_game_over(board)) {
            game_over();
            break;
        }
        draw_board(board);
    }

    // cleanup ncurses library
    endwin();

    return 0;
}

// initialize the game board
void init_board(int board[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

// generate a random tile (2 or 4) at a random position on the board
void generate_random_tile(int board[SIZE][SIZE]) {
    int i, j, r;
    do {
        i = rand() % SIZE;
        j = rand() % SIZE;
    } while (board[i][j] != 0);
    r = (rand() % 10 < 9) ? 2 : 4;
    board[i][j] = r;
}

// draw the game board in the terminal
void draw_board(int board[SIZE][SIZE]) {
    int i, j;
    clear();
    printw("2048\n\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printw("     .");
            }
            else {
                printw(" %5d", board[i][j]);
            }
        }
        printw("\n\n");
    }
    refresh();
}

// move the tiles in the specified direction
void move(char ch, int board[SIZE][SIZE]) {
    int i, j, k, l, m, n;
    int temp[SIZE][SIZE] = {0};
    int flag = 0;
    int size = SIZE;

    if (ch == 'a') {
        // move left
        for (i = 0; i < size; i++) {
            k = 0;
            for (j = 0; j < size; j++) {
                if (board[i][j] != 0) {
                    temp[i][k] = board[i][j];
                    if (j != k) {
                        flag = 1;
                    }
                    k++;
                }
            }
            for (j = 0; j < size - 1; j++) {
                if (temp[i][j] == temp[i][j + 1]) {
                    temp[i][j] *= 2;
                    temp[i][j + 1] = 0;
                    flag = 1;
                }
            }
            k = 0;
            for (j = 0; j < size; j++) {
                if (temp[i][j] != 0) {
                    board[i][k] = temp[i][j];
                    k++;
                }
            }
            for (j = k; j < size; j++) {
                board[i][j] = 0;
            }
        }
    }
    else if (ch == 'd') {
        // move right
        for (i = 0; i < size; i++) {
            k = size - 1;
            for (j = size - 1; j >= 0; j--) {
                if (board[i][j] != 0) {
                    temp[i][k] = board[i][j];
                    if (j != k) {
                        flag = 1;
                    }
                    k--;
                }
            }
            for (j = size - 1; j > 0; j--) {
                if (temp[i][j] == temp[i][j - 1]) {
                    temp[i][j] *= 2;
                    temp[i][j - 1] = 0;
                    flag = 1;
                }
            }
            k = size - 1;
            for (j = size - 1; j >= 0; j--) {
                if (temp[i][j] != 0) {
                    board[i][k] = temp[i][j];
                    k--;
                }
            }
            for (j = k; j >= 0; j--) {
                board[i][j] = 0;
            }
        }
    }
    else if (ch == 'w') {
        // move up
        for (j = 0; j < size; j++) {
            k = 0;
            for (i = 0; i < size; i++) {
                if (board[i][j] != 0) {
                    temp[k][j] = board[i][j];
                    if (i != k) {
                        flag = 1;
                    }
                    k++;
                }
            }
            for (i = 0; i < size - 1; i++) {
                if (temp[i][j] == temp[i + 1][j]) {
                    temp[i][j] *= 2;
                    temp[i + 1][j] = 0;
                    flag = 1;
                }
            }
            k = 0;
            for (i = 0; i < size; i++) {
                if (temp[i][j] != 0) {
                    board[k][j] = temp[i][j];
                    k++;
                }
            }
            for (i = k; i < size; i++) {
                board[i][j] = 0;
            }
        }
    }
    else if (ch == 's') {
        // move down
        for (j = 0; j < size; j++) {
            k = size - 1;
            for (i = size - 1; i >= 0; i--) {
                if (board[i][j] != 0) {
                    temp[k][j] = board[i][j];
                    if (i != k) {
                        flag = 1;
                    }
                    k--;
                }
            }
            for (i = size - 1; i > 0; i--) {
                if (temp[i][j] == temp[i - 1][j]) {
                    temp[i][j] *= 2;
                    temp[i - 1][j] = 0;
                    flag = 1;
                }
            }
            k = size - 1;
            for (i = size - 1; i >= 0; i--) {
                if (temp[i][j] != 0) {
                    board[k][j] = temp[i][j];
                    k--;
                }
            }
            for (i = k; i >= 0; i--) {
                board[i][j] = 0;
            }
        }
    }

    // generate a new tile if the board has changed
    if (flag) {
        generate_random_tile(board);
    }
}

// check if the game is over
int check_game_over(int board[SIZE][SIZE]) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) {
                return 0;
            }
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// display the game over screen
void game_over() {
    clear();
    printw("Game Over!\n\n");
    refresh();
}
