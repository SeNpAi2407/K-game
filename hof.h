#ifndef _HOF_H
#define _HOF_H

#include <stdbool.h>

#define SIZE 4
#define HOF_FILE "D:\\Works\\k\\score"
#define DELIMITER ' '

struct player {
    char name[30];
    int score;
};

int load(struct player list[]);
bool save(struct player list[], int size);
bool add_player(struct player list[], int* size, const struct player player);

void save_high_score(char board[SIZE][SIZE], int score);
void display_high_scores();

#endif



