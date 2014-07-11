#ifndef _GAME_H_
#define _GAME_H_

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>

#ifndef HORIZONTALSPACING
#define HORIZONTALSPACING 2
#endif

void swap_pointers(char **a,char **b);
void init_boards(char *primary_array, char *secondary_array, size_t width, size_t height);
void swap_boards(char *primary_array, char *secondary_array, size_t width, size_t height);
int get_numberof_neighbors(char *array, int x, int y, size_t width, size_t height);
void print_board(char *array, size_t width, size_t height);

#endif
