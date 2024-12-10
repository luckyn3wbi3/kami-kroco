#ifndef STRUCT_H
#define STRUCT_H

#define WIDTH 10
#define HEIGHT 10
#define NUM_MINES 10

typedef struct
{
  int is_open;
  int is_flag;
  int is_mine;
  int neig_mines;
} cell;

#endif