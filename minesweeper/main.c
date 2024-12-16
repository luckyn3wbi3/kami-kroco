/* Nama Program : main.c Tujuan : Modul utama untuk memanggil semua modul yang telah dibuat untuk menjalankan program Pembuat : Muhamad Syahid & Yazid Alrasyid */
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
        printf(" 1.Main \n");
        printf(" 2.Lihat Skor \n");
        printf(" 3.Lihat Leaderboard \n");
        printf("Opsi: ");
        scanf("%d", &opsi);
        if (opsi == 1)
        { 
            clear_terminal();
            srand(time(NULL));
            // Allocate memory for the game board
            cell **board = (cell **)malloc(WIDTH * sizeof(cell *));
            for (int i = 0; i < WIDTH; i++)
            {
                board[i] = (cell *)malloc(HEIGHT * sizeof(cell));
            }

            // Initialize the game board
            initialize_board(board, HEIGHT, WIDTH, NUM_MINES);

            // Start the game
            int result = 0;
            int game_result = play_game(board, HEIGHT, WIDTH, &result);

            // Get player name after the game ends
            char player_name[50];
            printf("Masukkan nama Anda: ");
            scanf("%s", player_name);

            // Generate binary file for the score
            generateBinary(player_name, result);

            // Free allocated memory for the board
            for (int i = 0; i < WIDTH; i++)
            {
                free(board[i]);
            }
            free(board);

            // Check if the game should continue
            if (game_result == 1)
            {
                clear_terminal();
                continue; // Restart the game
            }
            return 0; // Exit the program
        }
        else if (opsi == 2)
        {
            clear_terminal();
            readFileBinary("leaderboard_minesweeper_v-1.bin");
        }
        else if (opsi == 3)
        {
            clear_terminal();
            display_leaderboard("leaderboard_minesweeper_v-1.bin");
        }
        else
        {
            break; // Exit the loop
        }
    }
}