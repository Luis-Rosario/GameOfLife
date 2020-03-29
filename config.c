/*
 * Copyright (C) 2009 Raphael Kubo da Costa <kubito@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"
#include "mem.h"

/* Error messages */
/*static const char *const usage_message =
    "\n"
    "Conway's Game of Life\n"
    "Raphael Kubo da Costa, RA 072201\n"
    "\n"
    "Usage: glife GENERATIONS INPUT_FILE\n"
    "\n"
    "  GENERATIONS is the number of generations the game should run\n"
    "  INPUT_FILE  is a file containing an initial board state\n" "\n";*/

void game_config_free(GameConfig *config)
{
  if (config) {
    fclose(config->input_file);
    free(config);
  }
}

size_t game_config_get_generations(GameConfig *config)
{
  assert(config);

  return config->generations;
}

GameConfig *game_config_new_from_cli(int argc, char *argv[])
{
  char *endptr;
  FILE *file;
  GameConfig *config;
  long generations;

  int opt, nsecs, quit, pause, test, threads;
  char *map;
  pause = 0;
  quit = 0;
  test = 0;
  threads = 1;

  while ((opt = getopt(argc, argv, "qpt:")) != -1) {
      switch (opt) {
        case 'q':
          quit = 1;
          break;
        case 'p':
          nsecs = atoi(optarg);
          pause = 1;
          break; 
        case 't':
          test = 1;
          break;
      }
}
/*
  if (argc != CLI_ARGC) {
    fprintf(stderr, usage_message);
    return NULL;
  }
*/
if(pause == 1 && quit == 1){
  generations = strtol(argv[4], &endptr, 10);
    file = fopen(argv[5], "r");
    map = argv[5];
  
}

else if(pause == 1){
  generations = strtol(argv[3], &endptr, 10);
    file = fopen(argv[4], "r");
    map = argv[4];
  
}

else if(quit == 1){
  generations = strtol(argv[2], &endptr, 10);
    file = fopen(argv[3], "r");
    map = argv[3];
  
}

else if(test == 1){
  generations = strtol(argv[3], &endptr, 10);
  threads = strtol(argv[2], &endptr, 10);
  file = fopen(argv[4], "r");
  map = argv[4];
  
}

else{
  generations = strtol(argv[1], &endptr, 10);
  file = fopen(argv[2], "r");
  map = argv[2];
 
}

  if ((*endptr != '\0') || (generations < 0)) {
    fprintf(stderr, "Error: GENERATIONS must be a valid positive integer\n");
    printf("%lu",generations);
    return NULL;
  }

  if (!file) {
    fprintf(stderr, "Error: could not open '%s'\n", argv[2]);
    return NULL;
  }

  config = MEM_ALLOC(GameConfig);
  config->generations = (size_t) generations;
  config->input_file = file;
  config->quit = quit;
  config->pause = pause;
  config->nsecs = nsecs;
  config->test = test;
  config->threads = threads;
  config->map = map;

  return config;
}
