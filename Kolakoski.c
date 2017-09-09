/*
  Kolakoski.c v1.0
  Author: Sam Messick

  This program generates a Kolakoski sequence
  based on an integer input seed and a number
  of sequence generation iterations.

  The generation process takes an integer seed
  and generates a Kolakoski sequence using
  the sequence {seed, (seed-1)... 1}, outputting
  the resulting sequence in Kolakoski.txt, with
  the probability density of a '2' at each stage
  in the sequence. A file, Growth.txt lists the
  increase in size of the sequence during each Iteration.

  In the default Kolakoski seqence,(seed = 2),
  files Ones.txt and Twos.txt list locations of
  1's and 2's in the sequence.
*/


#include <stdio.h>
#include <stdlib.h>

/* input format: "Kolakoski <beginning seed number> <number of generation iterations>" */
int main(int argc, char* argv[])
{
  int iterations; // number of Kolakoski sequence generation iterations
  int seed;       // generator seed: first term in sequence
  iter_flag = sscanf(argv[2], "%d", &iterations);
  /* Default number of recursion iterations is 10 */
  if(!iterations_flag)
    iterations = 10;
  seed_flag = sscanf(argv[1], "%d", &seed);
  /* Default seed is 2 */
  if(!seed_flag)
    seed = 2;
  /* Create file for storing integer sequence.
     1's and 2's position files will be created
     in default case as well. */
  FILE* file = fopen("Kolakoski.txt", "w+");
  if(seed ==2)
  {
    FILE* ones_positions = fopen("Ones.txt", "w+"); // Position of 1's in sequence
    FILE* twos_positions = fopen("Twos.txt", "w+"); // Position of 2's in sequence
  }
  FILE* growth = fopen("Growth.txt", "w+");
  fprintf(file, "%d ", seed);
  rewind(file);

  int i;        // outer loop counter; counts iterations
  int j;        // number read from file; number of times curr_int should be printed
  int arr_ind;  // index in copying array
  int tmp = 0;  // holding variable for scanning sequence integers
  int future_array_size;  // Size of next copying array in sequence
  int curr_int;           // Current integer in sequence (between 1 and seed)
  int previous_array_size = 1;   // Size of integer seed set

  /* Iterate Kolakoski generation according to argv[2] */
  for(i = 0; i < iterations; i++)
  {
    // Calculate memory to allocate to storage array
    // to store next generation of Kolakoski sequence
    future_array_size = 0;
    while(fscanf(file, "%d", &tmp) == 1)
    {
      future_array_size += tmp;
    }

    /* Print change in sequence legnth in seperate document */
    fprintf(growth, "%d\n", future_array_size - previous_array_size);

    /* Allocate space for next generation of Kolakoski sequence */
    int* tmp_array = (int*) malloc(future_array_size * sizeof(int));

    /* Read contets of output file into newly allocated tmp_array */
    rewind(file);
    arr_ind = 0;
    curr_int = seed;
    while(fscanf(file, "%d", &tmp) == 1)
    {
      // Store curr_int tmp times in tmp_array
      for(j = 0; j < tmp; j++)
      {
        tmp_array[arr_ind] = curr_int;
        arr_ind++;
      }
      curr_int %= seed; // Update curr_int to alternating 1 or 2
      curr_int++;
    }

    /* Overwrite output file with tmp_array contents */
    rewind(file);
    for(j = 0; j < future_array_size; j++) {
      if(seed == 2 && i == iterations - 1)
      {
        if(tmp_array[j] == 1)
        {
          fprintf(ones_positions, "%d\n", j + 1);
        }
        else
          fprintf(twos_positions, "%d\n", j + 1);
      }
      fprintf(file, "%d ", tmp_array[j]);
    }
    previous_array_size = future_array_size;
    free(tmp_array);
    rewind(file);
  }

  /* Print probabilities of ones and twos occuring in sequence at each event *
   * A leading '1' is always presumed.                                       */

  FILE* output = fopen("Kolakoski_Output.txt", "w");

  /* Print probabilities of two occuring after 'total' events */
  int total = 1;  // Total number of counted terms in sequence
  int twos = 0;   // Number of counted 2's in sequence
  int current;    // Current term in counted sequence

  while(fscanf(file, "%d", &current) == 1)
  {
    total++;
    if(current == 2)
      twos++;
    fprintf(output, "%.20lf\n", ((double)twos)/total);
  }
}
