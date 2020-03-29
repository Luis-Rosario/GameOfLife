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

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "game.h"
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main(int argc, char *argv[])
{
  GameConfig *config;
  Game *game;
  size_t generation;

  config = game_config_new_from_cli(argc, argv);
  if (!config)
    exit(2);

  game = game_new();
  if (game_parse_board(game, config))
  {
    fprintf(stderr, "Could not read the board file.\n");

    game_config_free(config);
    game_free(game);

    exit(1);
  }

  int quit = config->quit;
  int pause = config->pause;
  int nsecs = config->nsecs;
  int test = config->test;
  int threads = config-> threads;
  double start = omp_get_wtime();

  if (pause == 1 || (pause == 0 && test == 0 && quit == 0))
  {
    printf("Seed board:\n");
    game_print_board(game);
    printf("\033[2J");
  }

  for (generation = 1; generation <= game_config_get_generations(config); generation++)
  {
    if (game_tick(game,threads))
    {
      fprintf(stderr, "Error while advancing to the next generation.\n");
      game_config_free(config);
      game_free(game);
    }

    if (quit == 0 && test == 0)
    {
      printf("\033[0;0H");
      printf("\nGeneration %zu:\n", generation);
      game_print_board(game);

      if (pause == 1)
      {
        sleep(nsecs);
      }
    }
  }

  if (quit == 1)
  {
    printf("\033[0;0H");
    printf("\nGeneration %zu:\n", generation - 1);
    game_print_board(game);
  }
  double end = omp_get_wtime();
  if(test == 1)
  {
    printf("n_generations: %ld\nn_threads: %d\nmap: %s\nrun_time %f\n",  generation - 1, threads, config-> map, end-start);
  }
  game_config_free(config);
  game_free(game);

  return 0;
}
