#include "board.h"

int errReason = 0;
char board[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

void errorcheck(int currentturn) {
    printf("\nError found at line %d; reason:\n", currentturn);
    switch (errReason) {
    case 0:
        puts("Undefined error");
        break;
    case 1:
        puts("Incorrect move: cannot stay in the same place");
        break;
    case 2:
        puts("Incorrect move: knight");
        break;
    case 3:
        puts("Incorrect move: king");
        break;
    case 4:
        puts("Incorrect move: bishop");
        break;
    case 5:
        puts("Incorrect move: rook");
        break;
    case 6:
        puts("Incorrect move: pawn");
        break;
    case 7:
        puts("Incorrect move: queen");
        break;
    case 8:
        puts("Incorrect attack/move notation");
        break;
    case 9:
        puts("Incorrect turn notation");
        break;
    case 10:
        puts("Out of bounds");
        break;
    case 11:
        puts("Incorrect piece notation");
        break;
    case 12:
        puts("Incorrect symbol post-move");
        break;
    }
}

int knight(int x, int y, int x1, int y1) {
    if ((y1 == y + 2 && x1 == x + 1) || (y1 == y + 2 && x1 == x - 1)
        || (y1 == y + 1 && x1 == x + 2) || (y1 == y + 1 && x1 == x - 2)
        || (y1 == y - 1 && x1 == x + 2) || (y1 == y - 1 && x1 == x - 2)
        || (y1 == y - 2 && x1 == x + 1) || (y1 == y - 2 && x1 == x - 1)) {
        return 1;
    }
    errReason = 2;
    return 0;
}

int king(int x, int y, int x1, int y1) {
    if ((abs(x1 - x) <= 1) && (abs(y1 - y) <= 1)) {
        return 1;
    }
    errReason = 3;
    return 0;
}

int bishop(int x, int y, int x1, int y1) {
    int i;
    if (abs(y1 - y) != abs(x1 - x)) {
        errReason = 4;
        return 0;
    }

    if (x1 > x && y1 > y) {
        // right-up
        for (i = 1; i < abs(x1 - x); i++) {
            if (board[x + i][y + i] != ' ') {
                errReason = 4;
                return 0;
            }
        }

    } else if (x1 < x && y1 < y) {
        // left-down
        for (i = 1; i < abs(x1 - x); i++) {
            if (board[x - i][y - i] != ' ') {
                errReason = 4;
                return 0;
            }
        }

    } else if (x1 > x && y1 < y) {
        // right-down
        for (i = 1; i < abs(x1 - x); i++) {
            if (board[x + i][y - i] != ' ') {
                errReason = 4;
                return 0;
            }
        }

    } else if (x1 < x && y1 > y) {
        // left-up
        for (i = 1; i < abs(x1 - x); i++) {
            if (board[x - i][y + i] != ' ') {
                errReason = 4;
                return 0;
            }
        }
    }

    return 1;
}

int rook(int x, int y, int x1, int y1) {
    int i;

    if (x1 != x && y1 != y) {
        errReason = 5;
        return 0;
    }

    if (x1 > x) {
        // left
        for (i = 1; (x - i) > x1; i++) {
            if (board[x - i][y] != ' ') {
                errReason = 5;
                return 0;
            }
        }

    } else if (x1 < x) {
        // right
        for (i = 1; (x + i) < x1; i++) {
            if (board[x + i][y] != ' ') {
                errReason = 5;
                return 0;
            }
        }

    } else if (y1 > y) {
        // up
        for (i = 1; (y + i) < y1; i++) {
            if (board[x][y + i] != ' ') {
                errReason = 5;
                return 0;
            }
        }

    } else if (y1 < y) {
        // down
        for (i = 1; (y - i) > y1; i++) {
            if (board[x][y - i] != ' ') {
                errReason = 5;
                return 0;
            }
        }
    }

    return 1;
}

int queen(int x, int y, int x1, int y1) {
    if (x == x1 || y == y1) {
        if (rook(x, y, x1, y1) == 1) {
            return 1;
        }
    } else if (abs(x1 - x) == abs(y1 - y)) {
        if (bishop(x, y, x1, y1) == 1) {
            return 1;
        }
    }
    errReason = 7;
    return 0;
}

int pawn(int x, int y, int x1, int y1) {
    int direction;
    if (board[x][y] >= 'A' && board[x][y] <= 'Z') {
        direction = 1;
    } else {
        direction = -1;
    }

    // first move
    if ((x == 1 && x1 == 3 && direction == 1)
        || (x == 6 && x1 == 4 && direction == -1)) {
        if (y1 - y == 0) {
            return 1;
        }
    }

    // slay
    if (board[x1][y1] != ' ') {
        if ((abs(y1 - y) == 1) && (x1 - x == direction)) {
            return 1;
        }
    }
    // regular
    if (board[x1][y1] == ' ') {
        if ((y - y1 == 0) && (x1 - x == direction)) {
            return 1;
        }
    }
    errReason = 6;
    return 0;
}

int slaycheck(char type, int x2, int y2, char fig, char color) {
    if (type == '-') {
        if (board[x2][y2] == ' ') {
            return 1;
        }
    } else if (type == 'x') {
        if (color == 'w') {
            if (board[x2][y2] >= 'a' && board[x2][y2] <= 'z') {
                return 1;
            }
        } else if (color == 'b') {
            if (board[x2][y2] >= 'A' && board[x2][y2] <= 'Z') {
                return 1;
            }
        }
    }

    errReason = 8;
    return 0;
}

int figurecheck(char fig, int x1, int y1, int x2, int y2) {
    switch (fig) {
    case 'P':
    case 'p':
        return pawn(x1, y1, x2, y2);

    case 'B':
    case 'b':
        return bishop(x1, y1, x2, y2);

    case 'R':
    case 'r':
        return rook(x1, y1, x2, y2);

    case 'N':
    case 'n':
        return knight(x1, y1, x2, y2);

    case 'Q':
    case 'q':
        return queen(x1, y1, x2, y2);

    case 'K':
    case 'k':
        return king(x1, y1, x2, y2);
    }
    return 0;
}

int castling() {
    return 0;
}

int movecheck(char x1, char y1, char x2, char y2, char slay, char fig) {
    int ix1, ix2, iy1, iy2;
    char color;

    ix1 = atoi(&y1) - 1;
    ix2 = atoi(&y2) - 1;
    iy1 = (int)x1 - 97;
    iy2 = (int)x2 - 97;

    // board limits
    if ((ix1 < 0) || (ix2 < 0) || (iy1 < 0) || (iy2 < 0) || (ix1 > 7)
        || (ix2 > 7) || (iy1 > 7) || (iy2 > 7)) {
        errReason = 10;
        return 0;
    }

    // different position
    if (ix1 == ix2 && iy1 == iy2) {
        errReason = 1;
        return 0;
    }

    if (fig >= 'A' && fig <= 'Z') {
        color = 'w';
    } else {
        color = 'b';
    }

    if ((board[ix1][iy1] == fig) && (figurecheck(fig, ix1, iy1, ix2, iy2))
        && (slaycheck(slay, ix2, iy2, fig, color))) {
        board[ix1][iy1] = ' ';
        if (fig == 'p' && x2 == 0) {
            board[ix2][iy2] = 'q';
        }
        if (fig == 'P' && x2 == 7) {
            board[ix2][iy2] = 'Q';
        } else {
            board[ix2][iy2] = fig;
        }
        return 1;
    }
    return 0;
}

int turnread(char* line, int currentturn) {
    char fig;
    int turnnum;
    turnnum = atoi(strtok(line, "."));

    if (turnnum != currentturn) {
        errReason = 9;
        return 0;
    }

    int index = 3 + (turnnum / 10);

    // white turn
    switch (line[index]) {
    case 'K':
        fig = 'K';
        index++;
        break;
    case 'Q':
        fig = 'Q';
        index++;
        break;
    case 'B':
        fig = 'B';
        index++;
        break;
    case 'N':
        fig = 'N';
        index++;
        break;
    case 'R':
        fig = 'R';
        index++;
        break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
        fig = 'P';
        break;
    case 'O':
        castling();
        break;
    default:
        errReason = 11;
        return 0;
    }

    if (movecheck(
                line[index],
                line[index + 1],
                line[index + 3],
                line[index + 4],
                line[index + 2],
                fig)
        == 0) {
        return 0;
    }

    switch (line[index + 5]) {
    case ' ':
    case '\0':
    case '\n':
        break;
    case '+':
        index++;
        break;
    case '#':
        return 2;
        break;
    default:
        errReason = 12;
        return 0;
    }
    // black turn
    index += 6;

    switch (line[index]) {
    case 'K':
        fig = 'k';
        index++;
        break;
    case 'Q':
        fig = 'q';
        index++;
        break;
    case 'B':
        fig = 'b';
        index++;
        break;
    case 'N':
        fig = 'n';
        index++;
        break;
    case 'R':
        fig = 'r';
        index++;
        break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
        fig = 'p';
        break;
    case 'O':
        castling();
        break;
    default:
        errReason = 11;
        return 0;
    }

    if (movecheck(
                line[index],
                line[index + 1],
                line[index + 3],
                line[index + 4],
                line[index + 2],
                fig)
        == 0) {
        return 0;
    }

    switch (line[index + 5]) {
    case ' ':
    case '\0':
    case '\n':
        break;
    case '+':
        index++;
        break;
    case '#':
        return 2;
        break;
    default:
        errReason = 12;
        return 0;
    }
    return 1;
}
