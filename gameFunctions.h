#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <stdbool.h>
#include "rectangle.h"

bool inTiles(int x, int y, int rows, int cols);
int bombsAroundTooMuch(int x, int y, int rows, int cols, Rect **tiles);
void generateBombs(int startRow, int startCol, int bombNum, DinRect *DinTiles);
void changeTileNumber(DinRect *DinTiles, int newRow, int newCol, int cellSize);
void calculateDistance(DinRect *DinTiles, double *distance, double cellSize, int width);
void setup(bool *generated, bool *inGame, int *row, int rowNum, int *col, int colNum, int *bombNum, int *flagNum, int bombs);
void setBombNums(int x, int y, DinRect *DinTiles);
void revealAllBombs(DinRect *DinTiles);
void findZerosAround(int x, int y, DinRect *DinTiles);
void revealTile(int x, int y, DinRect *DinTiles, bool *inGame);
void flagTile(DinRect *DinTiles, int x, int y, int *flagNum, int bombNum);




#endif
