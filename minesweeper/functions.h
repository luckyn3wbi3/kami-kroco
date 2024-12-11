/*
Nama Program : functions.h
Tujuan : Menyimpan beberapa model yang akan digunakan oleh program lainnya/ berguna sebagai header
Pembuat : Muhamad Syahid & Yazid Alrasyid
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h" // Menyertakan header structs.h

void initialize_board(cell **board, int height, int width, int num_mines);
void print_board(cell **board, int height, int width);
void print_cell(cell cell);
void place_mines(cell **board, int height, int width, int num_mines);
void calculate_neighbors(cell **board, int height, int width);
int open_cell(cell **board, int height, int width, int x, int y);
void flag_cell(cell **board, int height, int width, int x, int y);
int play_game(cell **board, int height, int width);
int score(cell **board,int height, int width);
void generateBinary(int result);
void readFileBinary(char *filename);

#endif
