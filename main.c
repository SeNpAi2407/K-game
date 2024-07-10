#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "k.h"
#include "hof.h"

void print_board(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '.') {
                printf(". ");
            } else {
                printf("%c ", board[i][j]);
            }
            if (j < SIZE - 1) {
                printf("| ");
            }
        }
        printf("\n");
        if (i < SIZE - 1) {
            printf("--|---|---|--\n");
        }
    }
    printf("\n");
}

int main() {
    struct game game;
    initialize_board(game.board);
    add_random_tile(game.board);
    add_random_tile(game.board);
    game.score = 0;

    char move;
    while (true) {
        print_board(game.board);
        printf("Score: %d\n", game.score);

        if (is_game_won(&game)) {
            printf("You won!\n");
            break;
        }

        if (!is_move_possible(&game)) {
            printf("Game over!\n");
            break;
        }

        printf("Enter move (w/a/s/d) or 'q' to quit: ");
        scanf(" %c", &move);

        if (move == 'q') {
            printf("Exiting the game...\n");
            break;
        }

        bool moved = false;
        switch (move) {
            case 'w':
                moved = update(&game, -1, 0);
                break;
            case 's':
                moved = update(&game, 1, 0);
                break;
            case 'a':
                moved = update(&game, 0, -1);
                break;
            case 'd':
                moved = update(&game, 0, 1);
                break;
            default:
                printf("Invalid move! Use w/a/s/d.\n");
        }

        if (!moved) {
            printf("Move not possible!\n");
        }
    }

    // Save the high score
    save_high_score(game.board, game.score);
    display_high_scores();

    return 0;
}












