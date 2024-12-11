/*
Nama Program : functions.c
Tujuan : Menyimpan beberapa modul (fungsi dan prosedur) yang akan digunakan oleh main.c
Pembuat : Muhamad Syahid & Yazid Alrasyid
*/
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

// Inisialisasi papan
void initialize_board(cell **board, int height, int width, int num_mines)
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      board[i][j].is_open = 0;
      board[i][j].is_flag = 0;
      board[i][j].is_mine = 0;
      board[i][j].neig_mines = 0;
    }
  }
  place_mines(board, height, width, num_mines);
  calculate_neighbors(board, height, width);
}

// Menempatkan ranjau secara acak
void place_mines(cell **board, int height, int width, int num_mines)
{
  int placed_mines = 0;
  while (placed_mines < num_mines)
  {
    int x = rand() % height;
    int y = rand() % width;
    if (board[x][y].is_mine == 0)
    {
      board[x][y].is_mine = 1;
      placed_mines++;
    }
  }
}

// Menghitung jumlah ranjau di sekitar setiap sel
void calculate_neighbors(cell **board, int height, int width)
{
  int directions[8][2] = {
      {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (board[i][j].is_mine)
      {
        continue;
      }
      int mine_count = 0;
      for (int k = 0; k < 8; k++)
      {
        int nx = i + directions[k][0];
        int ny = j + directions[k][1];
        if (nx >= 0 && ny >= 0 && nx < height && ny < width)
        {
          if (board[nx][ny].is_mine)
          {
            mine_count++;
          }
        }
      }
      board[i][j].neig_mines = mine_count;
    }
  }
}

// Menampilkan papan
void print_board(cell **board, int height, int width)
{
  printf("   ");
  for (int i = 0; i < width; i++)
  {
    printf("%d  ", i);
  }
  printf("\n");

  for (int i = 0; i < height; i++)
  {
    printf("%d ", i);
    for (int j = 0; j < width; j++)
    {
      print_cell(board[i][j]);
    }
    printf("\n");
  }
}

// Menampilkan setiap sel dengan simbol
void print_cell(cell cell)
{
  if (cell.is_flag == 1)
  {
    // printf("🚩 ");
    printf(" F ");
    return;
  }

  if (cell.is_open == 1)
  {
    if (cell.is_mine == 1)
    {
      // printf("💣 ");
      printf(" 0 ");
      return;
    }
    if (cell.neig_mines == 0)
    {
      // printf("🟩 ");
      printf(" - ");
      return;
    }
    switch (cell.neig_mines)
    {
    case 1:
      // printf("1️⃣ ");
      printf(" 1 ");
      break;
    case 2:
      // printf("2️⃣ ");
      printf(" 2 ");
      break;
    case 3:
      // printf("3️⃣ ");
      printf(" 3 ");
      break;
    case 4:
      // printf("4️⃣ ");
      printf(" 4 ");
      break;
    case 5:
      // printf("5️⃣ ");
      printf(" 5 ");
      break;
    case 6:
      // printf("6️⃣ ");
      printf(" 6 ");
      break;
    case 7:
      // printf("7️⃣ ");
      printf(" 7 ");
      break;
    case 8:
      // printf("8️⃣ ");
      printf(" 8 ");
      break;
    }
    return;
  }

  printf(" . ");
  // printf("⬜ ");
}

// Membuka sel
int open_cell(cell **board, int height, int width, int x, int y)
{
  if (board[x][y].is_open || board[x][y].is_flag)
  {
    return 0;
  }

  board[x][y].is_open = 1;

  if (board[x][y].is_mine)
  {
    return 1;
  }

  if (board[x][y].neig_mines == 0)
  {
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < 8; i++)
    {
      int nx = x + directions[i][0];
      int ny = y + directions[i][1];
      if (nx >= 0 && ny >= 0 && nx < height && ny < width)
      {
        if (!board[nx][ny].is_open)
        {
          open_cell(board, height, width, nx, ny);
        }
      }
    }
  }
  return 0;
}

// Memberi tanda bendera pada sel
void flag_cell(cell **board, int height, int width, int x, int y)
{
  if (board[x][y].is_open)
  {
    printf("Sel ini sudah dibuka, anda tidak bisa menandai ini dengan bendera\n");
    board[x][y].is_flag = !board[x][y].is_flag;
  }
  board[x][y].is_flag = !board[x][y].is_flag;
}

// Fungsi utama permainan
void play_game(cell **board, int height, int width)
{
  int game_over = 0;
  int flags = NUM_MINES;
  while (!game_over)
  {
    printf("\n===============================MINESWEEPER================================\n\n");
    print_board(board, height, width);
    printf("\nBendera yang tersisa: %d\n", flags);
    printf("Masukkan perintah (<o> <x> <y> untuk membuka, <f> <x> <y> untuk bendera): ");
    char command;
    int x, y;
    scanf(" %c %d %d", &command, &x, &y);

    if (x < 0 || x >= height || y < 0 || y >= width)
    {
      printf("Koordinat salah. Coba lagi.\n");
      continue;
    }
    int result = score(board, height, width);
    if (command == 'o')
    {
      game_over = open_cell(board, height, width, x, y);
      if (game_over)
      {
        printf("Anda terkena ranjau. Permainan Berakhir.\n");
        generateBinary(result);
        readFileBinary("score_minesweeper_v-1.bin");
      }
    }
    else if (command == 'f')
    {
      flag_cell(board, height, width, x, y);
      flags += board[x][y].is_flag ? -1 : board[x][y].is_open ? 0 : 1;
    }
    else
    {
      printf("Perintah tidak valid! Coba Lagi.\n");
    }

    if (flags == 0)
    {
      printf("Selamat! Kamu telah menghindari semua ranjau!.\n");
      generateBinary(result);
      readFileBinary("score_minesweeper_v-1.bin");
      break;
    }
  }
}

int score(cell **board, int height, int width)
{
  int sum_score = 0;
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (board[i][j].is_open)
      {
        sum_score += board[i][j].neig_mines;
      }
    }
  }
  return sum_score;
}

// Sebuah Procedure yang berfungsi untuk menyimpan data dari score dan menyimpannya dalam format bin
void generateBinary(int result)
{
  int versionFile = 1;
  char filename[50];
  sprintf(filename, "score_minesweeper_v-%d.bin", versionFile);
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL)
  {
    printf("Gagal membuka file score_minesweeper_v-%d.bin");
    return;
  }
  fwrite(&result, sizeof(result), 1, fp);
  fclose(fp);
}

// Sebuah Procedure yang berfungsi untuk membaca data dari score yang disimpan dalam format bin
void readFileBinary(char *filename)
{
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL)
  {
    printf("Gagal membuka file score_minesweeper_v-1.bin");
    return;
  }
  int result = 0;
  fread(&result, sizeof(result), 1, fp);
  printf("Skor anda = %d\n",result);
  fclose(fp);
}


