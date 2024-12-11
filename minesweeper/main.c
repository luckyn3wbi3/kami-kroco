/*
Nama Program : main.c
Tujuan : Modul utama untuk memanggil semua modul yang telah dibuat untuk menjalankan program
Pembuat : Muhamad Syahid & Yazid Alrasyid
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main()
{
  for (;;)
  {
    int opsi = 0;
    printf("========Minesweeper KamiKroco=========\n");
    printf("              1.Main              \n");
    printf("              2.Lihat Skor              \n");
    printf("Opsi: ");
    scanf("%d", &opsi);
    if (opsi == 1)
    {
      // Berfungsi untuk menghasilkan nilai random
      srand(time(NULL));

      // Membuat papan permainan
      // Berfungsi untuk alokasi memori untuk setiap barisnya
      cell **board = (cell **)malloc(WIDTH * sizeof(cell *));

      // Berfungsi untuk alokasi memori setiap kolom didalam setiap baris
      for (int i = 0; i < WIDTH; i++)
      {
        board[i] = (cell *)malloc(HEIGHT * sizeof(cell));
      }

      // Inisialisasi papan
      initialize_board(board, HEIGHT, WIDTH, NUM_MINES);

      // Mulai permainan
      int game_result = play_game(board, HEIGHT, WIDTH);
      if (game_result == 1)
      {
        continue;
      }
      return 0;
    }
    else if (opsi == 2)
    {
      readFileBinary("score_minesweeper_v-1.bin");
    }
    else
    {
      break;
    }
  }
}
