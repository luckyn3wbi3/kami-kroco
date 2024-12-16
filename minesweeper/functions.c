/* Nama Program : functions.c Tujuan : Menyimpan beberapa modul (fungsi dan prosedur) yang akan digunakan oleh main.c Pembuat : Muhamad Syahid & Yazid Alrasyid */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void clear_terminal()
{
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Linux and macOS
    #endif
}

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
  int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

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
  clear_terminal();
  printf("\n===============================MINESWEEPER================================\n\n");
  printf("  ");
  for (int i = 0; i < width; i++)
  {
    printf(" %d ", i);
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
        printf(" F "); // Display flag for non-mine
        return;
    }

    if (cell.is_open == 1)
    {
        if (cell.is_mine == 1)
        {
            printf(" X "); // Display X for opened mine
            return;
        }
        if (cell.neig_mines == 0)
        {
            printf(" - "); // Display empty cell
            return;
        }
        switch (cell.neig_mines)
        {
            case 1: printf(" 1 "); break;
            case 2: printf(" 2 "); break;
            case 3: printf(" 3 "); break;
            case 4: printf(" 4 "); break;
            case 5: printf(" 5 "); break;
            case 6: printf(" 6 "); break;
            case 7: printf(" 7 "); break;
            case 8: printf(" 8 "); break;
        }
        return;
    }

    printf(" . "); // Display unopened cell
}

// Menampilkan semua ranjau di papan
void reveal_mines(cell **board, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (board[i][j].is_mine)
            {
                board[i][j].is_open = 1; // Open the mine cell
            }
        }
    }
}

// Membuka sel
int open_cell(cell **board, int height, int width, int x, int y)
{
    clear_terminal();
    if (board[x][y].is_open || board[x][y].is_flag)
    {
        return 0;
    }

    board[x][y].is_open = 1;

    if (board[x][y].is_mine)
    {
        reveal_mines(board, height, width); // Reveal all mines
        return 1; // Game over
    }

    if (board[x][y].neig_mines == 0)
    {
        int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
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
int flag_cell(cell **board, int height, int width, int x, int y)
{
    clear_terminal();
    if (board[x][y].is_open)
    {
        printf("Sel ini sudah dibuka, anda tidak bisa menandai ini dengan bendera\n");
        return 0; // Cannot flag an opened cell
    }

    // Toggle the flag
    board[x][y].is_flag = !board[x][y].is_flag;

    // If the cell is a mine and is flagged, we can change its state
    if (board[x][y].is_flag && board[x][y].is_mine)
    {
        // Optionally, you can print a message here if you want
    }

    return 1; // Successfully flagged
}

// Fungsi utama permainan
int play_game(cell **board, int height, int width,int *result)
{
  clear_terminal();
  int game_over = 0;
  int flags = NUM_MINES;
  while (!game_over)
  {
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
    *result = score(board, height, width);
    if (command == 'o')
    {
      game_over = open_cell(board, height, width, x, y);
      if (game_over)
      {
          print_board(board, height, width); // Show the board with bombs
          printf("Anda terkena ranjau. Permainan Berakhir.\n");
          return 1;
      }
    }
    else if (command == 'f')
    {
      flag_cell(board, height, width, x, y);
      flags += board[x][y].is_flag ? -1 : board[x][y].is_open ? 0
                                                              : 1;
    }
    else
    {
      printf("Perintah tidak valid! Coba Lagi.\n");
    }

    if (flags == 0)
    {
      print_board(board, height, width); // Show the board with bombs
      printf("Selamat! Kamu telah menghindari semua ranjau!.\n");
      return 1;
    }
  }
  return 0;
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
void generateBinary(char player_name[50], int score)
{
    int versionFile = 1;
    char filename[50];
    sprintf(filename, "leaderboard_minesweeper_v-%d.bin", versionFile);
    FILE *fp = fopen(filename, "ab"); // Open in append mode
    if (fp == NULL)
    {
        printf("Gagal membuka file leaderboard_minesweeper_v-%d.bin\n", versionFile);
        return;
    }

    leaderboard_entry entry;
    strcpy(entry.name, player_name);
    entry.score = score;

    fwrite(&entry, sizeof(leaderboard_entry), 1, fp);
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
  printf("Skor anda = %d\n", result);
  fclose(fp);
}

void display_leaderboard(char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Gagal membuka file %s\n", filename);
        return;
    }

    leaderboard_entry entry;
    printf("======== Leaderboard ========\n");
    while (fread(&entry, sizeof(entry), 1, fp))
    {
        printf("Nama: %s, Skor: %d\n", entry.name, entry.score);
    }
    fclose(fp);
}