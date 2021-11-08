#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <stdbool.h>
#include "rectangle.h"

bool inTiles(int x, int y, int rows, int cols);
int bombsAroundTooMuch(int x, int y, int rows, int cols, Rect **tiles);
void generateBombs(int startRow, int startCol, int bombNum, DinRect *DinTiles);
void setup(bool *generated, bool *inGame, int *row, int rowNum, int *col, int colNum, int *bombNum, int *flagNum, int bombs/*, Rect **tiles, int cellSize*/); //<- adjuk hozzá ezeket
void setBombNums(int x, int y, DinRect *DinTiles);
void revealAllBombs(DinRect *DinTiles);
void findZerosAround(int x, int y, DinRect *DinTiles);
void revealTile(int x, int y, DinRect *DinTiles, bool *inGame);
void flagTile(/**/);




#endif
