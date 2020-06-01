#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int errReason;
extern char board[8][8];

void errorcheck(int currentturn);

int knight(int x, int y, int x1, int y1);
int king(int x, int y, int x1, int y1);
int bishop(int x, int y, int x1, int y1);
int rook(int x, int y, int x1, int y1);
int queen(int x, int y, int x1, int y1);
int pawn(int y, int x, int y1, int x1);

int slaycheck(char type, int x2, int y2, char fig, char color);
int figurecheck(char fig, int x1, int y1, int x2, int y2);
int movecheck(char x1, char y1, char x2, char y2, char slay, char fig);

int turnread(char* line, int currentturn);

#endif // BOARD_H
