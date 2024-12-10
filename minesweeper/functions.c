#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

// Inisialisasi papan
void initialize_board(cell board[HEIGHT][WIDTH], int height, int width, int num_mines)
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

// Menempatkan tambang secara acak
void place_mines(cell board[HEIGHT][WIDTH], int height, int width, int num_mines)
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

// Menghitung jumlah tambang di sekitar setiap sel
void calculate_neighbors(cell board[HEIGHT][WIDTH], int height, int width)
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
void print_board(cell board[HEIGHT][WIDTH], int height, int width)
{
  printf("   ");
  for (int i = 0; i < width; i++)
  {
    printf(" %d  ", i);
  }
  printf("\n");

  for (int i = 0; i < height; i++)
  {
    printf("%d  ", i);
    for (int j = 0; j < width; j++)
    {
      print_cell(board[i][j]);
    }
    printf("\n");
  }
}

// Menampilkan setiap sel dengan emoji
void print_cell(cell cell)
{
  if (cell.is_flag == 1)
  {
    printf("🚩 ");
    return;
  }

  if (cell.is_open == 1)
  {
    if (cell.is_mine == 1)
    {
      printf("💣 ");
      return;
    }
    if (cell.neig_mines == 0)
    {
      printf("🟩 ");
      return;
    }
    switch (cell.neig_mines)
    {
    case 1:
      printf("1️⃣ ");
      break;
    case 2:
      printf("2️⃣ ");
      break;
    case 3:
      printf("3️⃣ ");
      break;
    case 4:
      printf("4️⃣ ");
      break;
    case 5:
      printf("5️⃣ ");
      break;
    case 6:
      printf("6️⃣ ");
      break;
    case 7:
      printf("7️⃣ ");
      break;
    case 8:
      printf("8️⃣ ");
      break;
    }
    return;
  }

  printf("⬜ ");
}

// Membuka sel
int open_cell(cell board[HEIGHT][WIDTH], int height, int width, int x, int y)
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
void flag_cell(cell board[HEIGHT][WIDTH], int height, int width, int x, int y)
{
  if (board[x][y].is_open)
  {
    return;
  }
  board[x][y].is_flag = !board[x][y].is_flag;
}

// Fungsi utama permainan
void play_game(cell board[HEIGHT][WIDTH], int height, int width)
{
  int game_over = 0;
  int flags = NUM_MINES;
  while (!game_over)
  {
    print_board(board, height, width);
    printf("\nFlags left: %d\n", flags);
    printf("Enter command (o x y to open, f x y to flag): ");
    char command;
    int x, y;
    scanf(" %c %d %d", &command, &x, &y);

    if (x < 0 || x >= height || y < 0 || y >= width)
    {
      printf("Invalid coordinates! Try again.\n");
      continue;
    }

    if (command == 'o')
    {
      game_over = open_cell(board, height, width, x, y);
      if (game_over)
      {
        printf("Game Over! You hit a mine.\n");
      }
    }
    else if (command == 'f')
    {
      flag_cell(board, height, width, x, y);
      flags += board[x][y].is_flag ? -1 : 1;
    }
    else
    {
      printf("Invalid command! Try again.\n");
    }

    if (flags == 0)
    {
      printf("Congratulations! You've flagged all mines!\n");
      break;
    }
  }
}
