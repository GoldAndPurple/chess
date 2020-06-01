#include "board.h"
#include "board_print_terminal.h"

int main(int argc, char* argv[])
{
    FILE* source = fopen(argv[1], "r");
    if (source == NULL) {
        printf("Text file cannot be found\n");
        return 0;
    }
    char turnline[20];
    int counter = 0;
    int currentturn = 0;

    do {
        currentturn++;
        fgets(turnline, 20, source);
        counter = turnread(turnline, currentturn);
    } while (counter == 1);

    if (counter == 2) {
        printf("Match successfully read\nCheckmate at turn %d\n\n",
               currentturn);
        printBoardState(board);
    } else {
        errorcheck(currentturn);
    }

    fclose(source);

    return 0;
}
