#include "game.h"

//Note: live cells in the game are 1, dead are 0

int main(int argc, char *argv[])
{
   int size = 16;
   int sleep_duration = 1;
   int seed = 1;
   char lifeboard_a[size][size];
   char lifeboard_b[size][size];
   char *primary_array = *lifeboard_a;
   char *secondary_array = *lifeboard_b;

   srandom(seed);

   init_boards(*lifeboard_a, *lifeboard_b, size);

   while (1) {
      print_board(primary_array, size);
      swap_boards(primary_array, secondary_array, size);
      swap_pointers(&primary_array, &secondary_array);
      sleep(sleep_duration);
   }

   return 0;
}

void swap_pointers(char **a,char **b)
{
   char *temp = *a;
   *a = *b;
   *b = temp;

   return;
}

/* init_boards: init primary board with random numbers, secondary board all 0 */
// DONE: make this work for any array size, not just 64*64
void init_boards(char *primary_array, char *secondary_array, size_t array_size)
{
   int i, j;

   // init primary array
   for (i = 0; i < array_size; i++)
      for (j = 0; j < array_size; j++)
         primary_array[i*array_size+j] = (char)(random() % 2);

   // init secondary array
   for (i = 0; i < array_size; i++)
      for (j = 0; j < array_size; j++)
         secondary_array[i*array_size+j] = 0;
}

void swap_boards(char *primary_array, char *secondary_array, size_t array_size)
{
   int i, j;
   int num_neighbors;

   for (i = 0; i < array_size; i++)
      for (j = 0; j < array_size; j++) {
         num_neighbors = get_numberof_neighbors(primary_array, i, j, array_size);
         if (primary_array[i*array_size+j]) { // cell we're looking at is alive
            if (num_neighbors == 2 || num_neighbors == 3)
               secondary_array[i*array_size+j] = 1;
            else
               secondary_array[i*array_size+j] = 0;
         } else { // cell we're looking at is dead
            if (num_neighbors == 3)
               secondary_array[i*array_size+j] = 1;
            else
               secondary_array[i*array_size+j] = 0;
         }
      }
}


/* get_numberof_neighbors: count the number of neighbors to cell at [x][y] */
// DONE: make this work for any array size, not just 64*64
int get_numberof_neighbors(char *array, int x, int y, size_t array_size)
{
   // Array boundries
   int max = array_size;
   int xmin = x - 1;
   int xmax = x + 1;
   int ymin = y - 1;
   int ymax = y + 1;

   int i, j;
   int neighbors = 0;

   assert(x <= max && x >= 0);
   assert(y <= max && y >= 0);

   // test for special cases with array boundries
   if (x == max)
      xmax = max;
   if (x == 0)
      xmin = 0;
   if (y == max)
      ymax = max;
   if (y == 0)
      ymin = 0;

   // Move through array between boundries, counting live cells
   for (i = xmin; i <= xmax; i++)
      for (j = ymin; j <= ymax; j++)
         if (!(i == x && j == y))
            if (array[i*array_size+j])
               neighbors++;

   return neighbors;
}

void print_board(char *array, size_t array_size)
{
   int i, j;

   printf("\n");
   printf("\n");

   for (i = 0; i < array_size; i++) {
      for (j = 0; j < array_size; j++) {
         if (array[i*array_size+j])
            printf(" %d", array[i*array_size+j]);
         else
            printf("  ");
      }
      printf("\n");
   }

}
