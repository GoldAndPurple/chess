#include "board_print_terminal.h"

void printBoardState(char a[8][8])
{
    int i = 0, j = 0;
    for (i = 7; i >= 0; i--)
    {
        printf("%d ", i + 1);
        for (j = 0; j < 8; j++)
        {
            printf("%c ", a[i][j]);
        }
        printf("\n");
    }
    printf("  A B C D E F G H\n\n");
}
