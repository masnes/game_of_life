#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

void swap_pointers(char **a,char **b);
void init_boards(char *primary_array, char *secondary_array, size_t array_size);
void swap_boards(char *primary_array, char *secondary_array, size_t array_size);
int get_numberof_neighbors(char *array, int x, int y, size_t array_size);
void print_board(char *array, size_t array_size);

#endif
