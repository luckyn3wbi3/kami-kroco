/* Nama Program : functions.c
Tujuan : Menyimpan beberapa modul (fungsi dan prosedur) yang akan digunakan oleh main.c
Pembuat : Muhamad Syahid & Yazid Alrasyid */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// Fungsi untuk membersihkan terminal
void clear_terminal()
{
#ifdef _WIN32
  system("cls"); // Untuk Windows
#else
  system("clear"); // Untuk Linux dan macOS
#endif
}

// Inisialisasi papan permainan
void initialize_board(cell **board, int height, int width, int num_mines)
{
  // Mengatur semua sel di papan permainan ke status awal
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      board[i][j].is_open = 0;    // Sel belum dibuka
      board[i][j].is_flag = 0;    // Sel belum ditandai
      board[i][j].is_mine = 0;    // Sel bukan ranjau
      board[i][j].neig_mines = 0; // Jumlah ranjau di sekitar sel adalah 0
    }
  }
  // Menempatkan ranjau secara acak di papan
  place_mines(board, height, width, num_mines);
  // Menghitung jumlah ranjau di sekitar setiap sel
  calculate_neighbors(board, height, width);
}

// Menempatkan ranjau secara acak di papan
void place_mines(cell **board, int height, int width, int num_mines)
{
  int placed_mines = 0; // Menghitung jumlah ranjau yang telah ditempatkan
  while (placed_mines < num_mines)
  {
    int x = rand() % height; // Menghasilkan koordinat acak untuk baris
    int y = rand() % width;  // Menghasilkan koordinat acak untuk kolom
    // Jika sel tersebut bukan ranjau, tempatkan ranjau di sel tersebut
    if (board[x][y].is_mine == 0)
    {
      board[x][y].is_mine = 1; // Tandai sel sebagai ranjau
      placed_mines++;          // Tambah jumlah ranjau yang telah ditempatkan
    }
  }
}

// Menghitung jumlah ranjau di sekitar setiap sel
void calculate_neighbors(cell **board, int height, int width)
{
  // Arah untuk mengecek sel-sel di sekitar
  int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

  // Iterasi melalui setiap sel di papan
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      // Lewati sel yang merupakan ranjau
      if (board[i][j].is_mine)
      {
        continue;
      }
      int mine_count = 0; // Menghitung jumlah ranjau di sekitar sel
      // Mengecek semua arah di sekitar sel
      for (int k = 0; k < 8; k++)
      {
        int nx = i + directions[k][0]; // Koordinat baris sel tetangga
        int ny = j + directions[k][1]; // Koordinat kolom sel tetangga
        // Pastikan sel tetangga berada dalam batas papan
        if (nx >= 0 && ny >= 0 && nx < height && ny < width)
        {
          if (board[nx][ny].is_mine) // Jika sel tetangga adalah ranjau
          {
            mine_count++; // Tambah jumlah ranjau
          }
        }
      }
      board[i][j].neig_mines = mine_count; // Simpan jumlah ranjau di sel ini
    }
  }
}

// Menampilkan papan permainan
void print_board(cell **board, int height, int width)
{
  clear_terminal(); // Bersihkan terminal sebelum menampilkan papan
  printf("\n===============================MINESWEEPER================================\n\n");
  printf("  ");
  // Menampilkan indeks kolom
  for (int i = 0; i < width; i++)
  {
    printf(" %d ", i);
  }
  printf("\n");

  // Menampilkan setiap baris papan
  for (int i = 0; i < height; i++)
  {
    printf("%d ", i); // Menampilkan indeks baris
    for (int j = 0; j < width; j++)
    {
      print_cell(board[i][j]); // Menampilkan setiap sel di baris
    }
    printf("\n"); // Pindah ke baris berikutnya
  }
}

// Menampilkan setiap sel dengan simbol yang sesuai
void print_cell(cell cell)
{
  if (cell.is_flag == 1)
  {
    printf(" F "); // Menampilkan bendera untuk sel yang ditandai
    return;
  }

  if (cell.is_open == 1)
  {
    if (cell.is_mine == 1)
    {
      printf(" X "); // Menampilkan X untuk ranjau yang dibuka
      return;
    }
    if (cell.neig_mines == 0)
    {
      printf(" - "); // Menampilkan sel kosong
      return;
    }
    // Menampilkan jumlah ranjau di sekitar sel
    switch (cell.neig_mines)
    {
    case 1:
      printf(" 1 ");
      break;
    case 2:
      printf(" 2 ");
      break;
    case 3:
      printf(" 3 ");
      break;
    case 4:
      printf(" 4 ");
      break;
    case 5:
      printf(" 5 ");
      break;
    case 6:
      printf(" 6 ");
      break;
    case 7:
      printf(" 7 ");
      break;
    case 8:
      printf(" 8 ");
      break;
    }
    return;
  }

  printf(" . "); // Menampilkan sel yang belum dibuka
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
        board[i][j].is_open = 1; // Membuka sel ranjau
      }
    }
  }
}

// Membuka sel pada papan
int open_cell(cell **board, int height, int width, int x, int y)
{
  clear_terminal(); // Bersihkan terminal sebelum membuka sel
  if (board[x][y].is_open || board[x][y].is_flag)
  {
    return 0; // Sel sudah dibuka atau ditandai, tidak bisa dibuka lagi
  }

  board[x][y].is_open = 1; // Tandai sel sebagai dibuka

  if (board[x][y].is_mine)
  {
    reveal_mines(board, height, width); // Mengungkap semua ranjau
    return 1;                           // Permainan berakhir
  }

  if (board[x][y].neig_mines == 0)
  {
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < 8; i++)
    {
      int nx = x + directions[i][0]; // Koordinat baris sel tetangga
      int ny = y + directions[i][1]; // Koordinat kolom sel tetangga
      // Pastikan sel tetangga belum dibuka
      if (nx >= 0 && ny >= 0 && nx < height && ny < width)
      {
        if (!board[nx][ny].is_open)
        {
          open_cell(board, height, width, nx, ny); // Buka sel tetangga
        }
      }
    }
  }
  return 0; // Permainan belum berakhir
}

// Memberi tanda bendera pada sel
int flag_cell(cell **board, int height, int width, int x, int y, int *is_correct)
{
  clear_terminal(); // Bersihkan terminal sebelum memberi tanda
  if (board[x][y].is_open)
  {
    printf("Sel ini sudah dibuka, anda tidak bisa menandai ini dengan bendera\n");
    return 0; // Tidak bisa memberi tanda pada sel yang sudah dibuka
  }

  // Mengubah status bendera
  board[x][y].is_flag = !board[x][y].is_flag;

  // Jika sel adalah ranjau dan ditandai, periksa kevalidan
  if (board[x][y].is_flag && board[x][y].is_mine)
  {
    valid_flags(is_correct); // Validasi bendera
  }

  return 1; // Berhasil memberi tanda
}

// Memvalidasi jumlah bendera yang benar
int valid_flags(int *correct)
{
  return (*correct)++; // Menambah jumlah bendera yang benar
}

// Fungsi utama permainan
int play_game(cell **board, int height, int width, int num_mines, int *result)
{
  clear_terminal();      // Bersihkan terminal sebelum memulai permainan
  int game_over = 0;     // Status permainan
  int flags = num_mines; // Jumlah bendera yang tersedia
  int is_correct = 0;    // Jumlah bendera yang benar
  while (!game_over)
  {
    print_board(board, height, width);             // Tampilkan papan permainan
    printf("\nBendera yang tersisa: %d\n", flags); // Tampilkan jumlah bendera yang tersisa
    printf("Masukkan perintah (<o> <baris> <kolom> untuk membuka, <f> <baris> <kolom> untuk bendera): ");
    char command;                         // Perintah dari pengguna
    int x, y;                             // Koordinat sel
    scanf(" %c %d %d", &command, &x, &y); // Ambil input dari pengguna
    if (x < 0 || x >= height || y < 0 || y >= width)
    {
      printf("Koordinat salah. Coba lagi.\n"); // Validasi koordinat
      continue;
    }
    *result = score(board, height, width); // Hitung skor saat ini
    if (command == 'o')                    // Jika perintah adalah membuka sel
    {
      game_over = open_cell(board, height, width, x, y); // Buka sel
      if (game_over)
      {
        print_board(board, height, width);                    // Tampilkan papan dengan ranjau
        printf("Anda terkena ranjau. Skor anda = %d .Permainan Berakhir.\n",*result); // Pesan game over
        return 1;                                             // Kembali dengan status game over
      }
    }
    else if (command == 'f') // Jika perintah adalah memberi tanda
    {
      flag_cell(board, height, width, x, y, &is_correct); // Beri tanda pada sel
      flags += board[x][y].is_flag ? -1 : board[x][y].is_open ? 0
                                                              : 1; // Update jumlah bendera
    }
    else
    {
      printf("Perintah tidak valid! Coba Lagi.\n"); // Pesan perintah tidak valid
    }
    if (is_correct == num_mines) // Jika semua ranjau ditandai dengan benar
    {
      print_board(board, height, width);                          // Tampilkan papan dengan ranjau
      printf("Selamat! Kamu telah menghindari semua ranjau!. Skor anda = %d \n",*result); // Pesan kemenangan
      return 1;                                                   // Kembali dengan status menang
    }
  }
  return 0; // Kembali dengan status permainan berlanjut
}

// Menghitung skor berdasarkan sel yang dibuka
int score(cell **board, int height, int width)
{
  int sum_score = 0; // Inisialisasi skor
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (board[i][j].is_open) // Jika sel dibuka
      {
        sum_score += board[i][j].neig_mines; // Tambah skor dengan jumlah ranjau di sekitar
      }
    }
  }
  return sum_score; // Kembalikan total skor
}

// Sebuah Procedure yang berfungsi untuk menyimpan data dari score dan menyimpannya dalam format bin
void saveScore(char player_name[50], int score)
{
  int versionFile = 1;                                                // Versi file leaderboard
  char filename[50];                                                  // Nama file
  sprintf(filename, "leaderboard_minesweeper_v-%d.bin", versionFile); // Format nama file
  FILE *fp = fopen(filename, "ab");                                   // Buka file dalam mode append
  if (fp == NULL)
  {
    printf("Gagal membuka file leaderboard_minesweeper_v-%d.bin\n", versionFile); // Pesan gagal membuka file
    return;
  }

  leaderboard_entry entry;         // Struktur untuk menyimpan entri leaderboard
  strcpy(entry.name, player_name); // Salin nama pemain
  entry.score = score;             // Simpan skor

  fwrite(&entry, sizeof(leaderboard_entry), 1, fp); // Tulis entri ke file
  fclose(fp);                                       // Tutup file
}

// Menampilkan leaderboard dari file
void display_leaderboard(char *filename)
{
  clear_terminal();                 // Bersihkan terminal sebelum menampilkan leaderboard
  FILE *fp = fopen(filename, "rb"); // Buka file dalam mode baca biner
  if (fp == NULL)
  {
    printf("Gagal membuka file %s\n", filename); // Pesan gagal membuka file
    return;
  }

  // Menghitung berapa banyak data yang ada didalam file
  fseek(fp, 0, SEEK_END);                           // Pindah ke akhir file
  long fileSize = ftell(fp);                        // Dapatkan ukuran file
  int count = fileSize / sizeof(leaderboard_entry); // Hitung jumlah entri
  rewind(fp);                                       // Kembali ke awal file

  // Alokasi memori untuk setiap data array
  leaderboard_entry *entries = (leaderboard_entry *)malloc(count * sizeof(leaderboard_entry));
  if (entries == NULL)
  {
    printf("Alokasi Memori Gagal\n"); // Pesan gagal alokasi memori
    fclose(fp);                       // Tutup file
    return;
  }

  // Membaca semua data didalam file
  fread(entries, sizeof(leaderboard_entry), count, fp); // Baca entri dari file
  fclose(fp);                                           // Tutup file

  // Sortir data berdasarkan score dengan metode qsort
  qsort(entries, count, sizeof(leaderboard_entry), sort_score); // Urutkan entri berdasarkan skor

  // Menampilkan 10 besar
  printf("======== Top 10 Leaderboard ========\n");
  for (int i = 0; i < count && i < 10; i++)
  {
    printf("Nama: %s, Skor: %d\n", entries[i].name, entries[i].score); // Tampilkan nama dan skor
  }

  // Membersihkan alokasi memory
  free(entries); // Bebaskan memori yang dialokasikan
}

// Menampilkan panduan permainan dari file
void guides(char *filename)
{
  clear_terminal();                // Bersihkan terminal sebelum menampilkan panduan
  FILE *fp = fopen(filename, "r"); // Buka file dalam mode baca
  if (fp == NULL)
  {
    printf("Gagal membuka file aturan-main.txt"); // Pesan gagal membuka file
    return;
  }

  char buffer[4096]; // Buffer untuk menyimpan baris
  int line = 1;      // Inisialisasi nomor baris

  while (fgets(buffer, sizeof(buffer), fp) != NULL) // Baca setiap baris
  {
    printf("%s", buffer); // Tampilkan baris
    line++;               // Tambah nomor baris
  }

  fclose(fp); // Tutup file
}

// Fungsi untuk mengurutkan skor
int sort_score(const void *a, const void *b)
{
  leaderboard_entry *entryA = (leaderboard_entry *)a; // Cast ke tipe leaderboard_entry
  leaderboard_entry *entryB = (leaderboard_entry *)b; // Cast ke tipe leaderboard_entry
  return entryB->score - entryA->score;               // Urutkan berdasarkan skor secara menurun
}