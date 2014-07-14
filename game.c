#include "game.h"

//Note: live cells in the game are >= 1, dead are 0

int main(int argc, char *argv[])
{
   struct winsize w;
   struct timespec tspec;
   int width, height;
   int seed = time(NULL);
   char **primary_array;
   char **secondary_array;
   int sleep_seconds = 0;
   int sleep_nanosecs = 150000000;
   tspec.tv_sec = sleep_seconds;
   tspec.tv_nsec = sleep_nanosecs;

   srandom(seed);

   // get window information
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

   // set size based on window info
   width = w.ws_col / HORIZONTALSPACING;
   height = w.ws_row - 2;


   char *lifeboard_a = malloc(sizeof(char) * width * height);
   char *lifeboard_b = malloc(sizeof(char) * width * height);

   if (lifeboard_a == NULL || lifeboard_b == NULL) {
      fprintf(stderr, "Error: out of memory\n");
      exit(1);
   }

   primary_array = &lifeboard_a;
   secondary_array = &lifeboard_b;

   init_boards(lifeboard_a, lifeboard_b, width, height);

   while (1) {
      print_board(*primary_array, width, height);
      swap_boards(*primary_array, *secondary_array, width, height);
      swap_pointers(primary_array, secondary_array);
      nanosleep(&tspec, NULL);
   }

   free(lifeboard_a);
   free(lifeboard_b);

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
void init_boards(char *primary_array, char *secondary_array, size_t width, size_t height)
{
   int i, j;

   // init primary array
   for (i = 0; i < width; i++)
      for (j = 0; j < height; j++)
         primary_array[i*height+j] = (char)(random() % 2);

   // init secondary array
   for (i = 0; i < width; i++)
      for (j = 0; j < height; j++)
         secondary_array[i*height+j] = 0;
}

/* swap_boards: using the state of primary_array, build secondary_array */
void swap_boards(char *primary_array, char *secondary_array, size_t width, size_t height)
{
   int i, j;
   int num_neighbors;

   for (i = 0; i < height; i++)
      for (j = 0; j < width; j++) {
         num_neighbors = get_numberof_neighbors(primary_array, i, j, width, height);
         if (primary_array[i*height+j]) { // cell we're looking at is alive
            if (num_neighbors == 2 || num_neighbors == 3)
               secondary_array[i*height+j] = num_neighbors;
            else
               secondary_array[i*height+j] = 0;
         } else { // cell we're looking at is dead
            if (num_neighbors == 3)
               secondary_array[i*height+j] = num_neighbors;
            else
               secondary_array[i*height+j] = 0;
         }
      }
}


/* get_numberof_neighbors: count the number of neighbors to cell at [x][y] */
int get_numberof_neighbors(char *array, int x, int y, size_t width, size_t height)
{
   // Array boundries
   int heightmax = height-1;
   int widthmax = width-1;
   int xmin = x - 1;
   int xmax = x + 1;
   int ymin = y - 1;
   int ymax = y + 1;

   int i, j;
   int neighbors = 0;

   assert(x <= heightmax && x >= 0);
   assert(y <= widthmax && y >= 0);

   // test for special cases with array boundries
   if (x == heightmax)
      xmax = heightmax;
   if (x == 0)
      xmin = 0;
   if (y == widthmax)
      ymax = widthmax;
   if (y == 0)
      ymin = 0;

   // Move through array between boundries, counting live cells
   for (i = xmin; i <= xmax; i++)
      for (j = ymin; j <= ymax; j++)
         if (!(i == x && j == y))
            if (array[i*height+j])
               neighbors++;

   return neighbors;
}

/*
 * print_board: print board state as 2d "image"
 * X's are alive, " "'s are dead.
 */
void print_board(char *array, size_t width, size_t height)
{
   int i, j, k;

   for (i = 0; i < 10; i++)
      printf("\n");

   for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
         if (array[i*height+j]) {
            for (k = 1; k < HORIZONTALSPACING; k++)
               printf(" ");
            printf("X");
         }
         else
            for (k = 1; k <= HORIZONTALSPACING; k++)
               printf(" ");
      }
      printf("\n");
   }

}
