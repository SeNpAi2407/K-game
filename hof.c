#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hof.h"

#define MAX_PLAYERS 10

void save_high_score(char board[SIZE][SIZE], int score) {
    struct player list[MAX_PLAYERS];
    int size = load(list);

    struct player new_player;
    printf("Enter your name: ");
    scanf("%s", new_player.name);
    new_player.score = score;

    if (add_player(list, &size, new_player)) {
        if (!save(list, size)) {
            printf("Error saving high scores\n");
        } else {
            printf("High scores saved successfully.\n");
        }
    }
}

void display_high_scores() {
    struct player list[MAX_PLAYERS];
    int size = load(list);

    printf("TOP:\n");
    for (int i = 0; i < size; i++) {
        printf("%s: %d\n", list[i].name, list[i].score);
    }
}

int load(struct player list[]) {
    FILE *file = fopen(HOF_FILE, "r");
    if (!file) {
        perror("Error opening file for reading");
        return 0;
    }

    int i = 0;
    while (fscanf(file, "%s %d", list[i].name, &list[i].score) == 2) {
        i++;
    }

    fclose(file);
    return i;
}

bool save(struct player list[], int size) {
    FILE *file = fopen(HOF_FILE, "w");
    if (!file) {
        perror("Error opening file for writing");
        return false;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %d\n", list[i].name, list[i].score);
    }

    fclose(file);
    return true;
}

bool add_player(struct player list[], int* size, const struct player new_player) {
    for (int i = 0; i < *size; i++) {
        if (strcmp(list[i].name, new_player.name) == 0) {
            if (new_player.score > list[i].score) {
                list[i].score = new_player.score;
            }
            return true;
        }
    }
    if (*size < MAX_PLAYERS) {
        list[*size] = new_player;
        (*size)++;
    } else {
        int min_index = 0;
        for (int i = 1; i < MAX_PLAYERS; i++) {
            if (list[i].score < list[min_index].score) {
                min_index = i;
            }
        }
        if (new_player.score > list[min_index].score) {
            list[min_index] = new_player;
        } else {
            return false;
        }
    }
    for (int i = 0; i < *size - 1; i++) {
        for (int j = i + 1; j < *size; j++) {
            if (list[i].score < list[j].score) {
                struct player temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }

    return true;
}










