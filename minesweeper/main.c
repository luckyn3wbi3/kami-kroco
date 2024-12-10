#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define WIDTH 10
#define HEIGHT 10
#define NUM_MINES 10

int main()
{
  srand(time(NULL));

  // Membuat papan permainan
  cell board[HEIGHT][WIDTH];

  // Inisialisasi papan
  initialize_board(board, HEIGHT, WIDTH, NUM_MINES);

  // Mulai permainan
  play_game(board, HEIGHT, WIDTH);

  return 0;
}
