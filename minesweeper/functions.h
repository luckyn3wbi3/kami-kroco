#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "struct.h" // Menyertakan header struct.h

void initialize_board(cell board[HEIGHT][WIDTH], int height, int width, int num_mines);
void print_board(cell board[HEIGHT][WIDTH], int height, int width);
void print_cell(cell cell);
void place_mines(cell board[HEIGHT][WIDTH], int height, int width, int num_mines);
void calculate_neighbors(cell board[HEIGHT][WIDTH], int height, int width);
int open_cell(cell board[HEIGHT][WIDTH], int height, int width, int x, int y);
void flag_cell(cell board[HEIGHT][WIDTH], int height, int width, int x, int y);
void play_game(cell board[HEIGHT][WIDTH], int height, int width);

#endif
