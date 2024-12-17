/*
Nama Program : structs.h
Tujuan : Menyimpan sebuah struct kolom yang akan digunakan oleh program minesweeper
Pembuat : Yazid Alrasyid
*/
#ifndef STRUCTS_H
#define STRUCTS_H

// Structure to represent a cell in the Minesweeper board
typedef struct
{
  int is_open;    // Indicates if the cell is opened
  int is_flag;    // Indicates if the cell is flagged
  int is_mine;    // Indicates if the cell contains a mine
  int neig_mines; // Number of neighboring mines
} cell;

// Structure to represent a leaderboard entry
typedef struct
{
    char name[50]; // Player's name
    int score;     // Player's score
} leaderboard_entry;

#endif // STRUCTS_H