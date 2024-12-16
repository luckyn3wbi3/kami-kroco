/*
Nama Program : functions.h
Tujuan : Menyimpan beberapa model yang akan digunakan oleh program lainnya/ berguna sebagai header
Pembuat : Muhamad Syahid & Yazid Alrasyid
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h" // Menyertakan header structs.h

// Function declarations
void clear_terminal();
void initialize_board(cell **board, int height, int width, int num_mines);
void print_board(cell **board, int height, int width);
void print_cell(cell cell);
void place_mines(cell **board, int height, int width, int num_mines);
void calculate_neighbors(cell **board, int height, int width);
void reveal_mines(cell **board, int height, int width);
int open_cell(cell **board, int height, int width, int x, int y);
int play_game(cell **board, int height, int width, int *result);
int flag_cell(cell **board, int height, int width, int x, int y);
int score(cell **board, int height, int width);
void generateBinary(char player_name[50], int score);
void readFileBinary(char *filename);
void display_leaderboard(char *filename);

#endif // FUNCTIONS_H