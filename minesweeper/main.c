#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main()
{
  //Berfungsi untuk menghasilkan nilai random
  srand(time(NULL));

  // Membuat papan permainan
  //Berfungsi untuk alokasi memori untuk setiap barisnya
  cell **board = (cell **)malloc(WIDTH * sizeof(cell *));

  //Berfungsi untuk alokasi memori setiap kolom didalam setiap baris
  for (int i = 0; i < WIDTH;i++){ 
    board[i] = (cell *)malloc(HEIGHT * sizeof(cell));
  }

  // Inisialisasi papan
  initialize_board(board, HEIGHT, WIDTH, NUM_MINES);

  // Mulai permainan
  play_game(board, HEIGHT, WIDTH);

  return 0;
}
