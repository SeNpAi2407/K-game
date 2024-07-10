#include "k.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void initialize_board(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

void add_random_tile(char board[SIZE][SIZE]) {
    int empty_tiles[SIZE * SIZE][2];
    int empty_count = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '.') {
                empty_tiles[empty_count][0] = i;
                empty_tiles[empty_count][1] = j;
                empty_count++;
            }
        }
    }

    if (empty_count > 0) {
        int random_tile = rand() % empty_count;
        char new_tile = (rand() % 2 == 0) ? 'A' : 'B';
        board[empty_tiles[random_tile][0]][empty_tiles[random_tile][1]] = new_tile;
    }
}


bool is_game_won(const struct game *game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game->board[i][j] == 'K') {
                return true;
            }
        }
    }
    return false;
}

bool is_move_possible(const struct game *game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game->board[i][j] == ' ') {
                return true;
            }
            if (i < SIZE - 1 && game->board[i][j] == game->board[i + 1][j]) {
                return true;
            }
            if (j < SIZE - 1 && game->board[i][j] == game->board[i][j + 1]) {
                return true;
            }
        }
    }
    return false;
}

bool update(struct game *game, int dy, int dx) {
    if ((dy != 0 && dx != 0) || (dy == 0 && dx == 0)) {
        return false;
    }

    bool moved = false;

    if (dx == 1) { // Move right
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE - 2; j >= 0; j--) {
                if (game->board[i][j] != '.') {
                    int k = j;
                    while (k + 1 < SIZE && game->board[i][k + 1] == '.') {
                        game->board[i][k + 1] = game->board[i][k];
                        game->board[i][k] = '.';
                        k++;
                        moved = true;
                    }
                    if (k + 1 < SIZE && game->board[i][k + 1] == game->board[i][k]) {
                        game->board[i][k + 1]++;
                        game->score += (1 << (game->board[i][k + 1] - 'A' + 1));
                        game->board[i][k] = '.';
                        moved = true;
                    }
                }
            }
        }
    } else if (dx == -1) { // Move left
        for (int i = 0; i < SIZE; i++) {
            for (int j = 1; j < SIZE; j++) {
                if (game->board[i][j] != '.') {
                    int k = j;
                    while (k - 1 >= 0 && game->board[i][k - 1] == '.') {
                        game->board[i][k - 1] = game->board[i][k];
                        game->board[i][k] = '.';
                        k--;
                        moved = true;
                    }
                    if (k - 1 >= 0 && game->board[i][k - 1] == game->board[i][k]) {
                        game->board[i][k - 1]++;
                        game->score += (1 << (game->board[i][k - 1] - 'A' + 1));
                        game->board[i][k] = '.';
                        moved = true;
                    }
                }
            }
        }
    } else if (dy == 1) { // Move down
        for (int j = 0; j < SIZE; j++) {
            for (int i = SIZE - 2; i >= 0; i--) {
                if (game->board[i][j] != '.') {
                    int k = i;
                    while (k + 1 < SIZE && game->board[k + 1][j] == '.') {
                        game->board[k + 1][j] = game->board[k][j];
                        game->board[k][j] = '.';
                        k++;
                        moved = true;
                    }
                    if (k + 1 < SIZE && game->board[k + 1][j] == game->board[k][j]) {
                        game->board[k + 1][j]++;
                        game->score += (1 << (game->board[k + 1][j] - 'A' + 1));
                        game->board[k][j] = '.';
                        moved = true;
                    }
                }
            }
        }
    } else if (dy == -1) { // Move up
        for (int j = 0; j < SIZE; j++) {
            for (int i = 1; i < SIZE; i++) {
                if (game->board[i][j] != '.') {
                    int k = i;
                    while (k - 1 >= 0 && game->board[k - 1][j] == '.') {
                        game->board[k - 1][j] = game->board[k][j];
                        game->board[k][j] = '.';
                        k--;
                        moved = true;
                    }
                    if (k - 1 >= 0 && game->board[k - 1][j] == game->board[k][j]) {
                        game->board[k - 1][j]++;
                        game->score += (1 << (game->board[k - 1][j] - 'A' + 1));
                        game->board[k][j] = '.';
                        moved = true;
                    }
                }
            }
        }
    }

    if (moved) {
        add_random_tile(game->board);
    }
    return moved;
}









