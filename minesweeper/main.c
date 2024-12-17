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
        int width = 0;
        int height = 0;
        int num_mines = 0;
        printf("========Minesweeper KamiKroco=========\n");
        printf(" 1.Main \n");
        printf(" 2.Petunjuk Permainan \n");
        printf(" 3.Lihat Leaderboard \n");
        printf("Opsi: ");
        scanf("%d", &opsi);
        if (opsi == 1)
        { 
            clear_terminal();
            int opsi_diff = 0;
            printf("========Pilih Kesulitan=========\n");
            printf(" 1.Mudah 9x9 10 Ranjau \n");
            printf(" 2.Sedang 16x16 40 Ranjau \n");
            printf(" 3.Sulit 30x16 99 Ranjau \n");
            printf(" 4.Custom \n");
            printf("Opsi: ");
            scanf("%d", &opsi_diff);
            switch (opsi_diff)
            {
            case 1:
                width = 9;
                height = 9;
                num_mines = 10;
                break;
            case 2:
                width = 16;
                height = 16;
                num_mines = 40;
                break;
            case 3:
                width = 30;
                height = 16;
                num_mines = 99;
                break;
            case 4:
                printf("Baris? ");
                scanf("%d",&height);
                printf("Kolom? ");
                scanf("%d",&width);
                printf("Jumlah Ranjau? ");
                scanf("%d",&num_mines);
                break;
            default:
                break;
            }
            srand(time(NULL));
            // Allocate memory for the game board
            cell **board = (cell **)malloc(width * sizeof(cell *));
            for (int i = 0; i < width; i++)
            {
                board[i] = (cell *)malloc(height * sizeof(cell));
            }

            // Initialize the game board
            initialize_board(board, height, width, num_mines);

            // Start the game
            int result = 0;
            int game_result = play_game(board, height, width, num_mines, &result);

            // Get player name after the game ends
            char player_name[50];
            printf("Masukkan nama Anda: ");
            scanf("%s", player_name);

            // Generate binary file for the score
            saveScore(player_name, result);

            // Free allocated memory for the board
            for (int i = 0; i < width; i++)
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
            guides("aturan-main.txt");
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