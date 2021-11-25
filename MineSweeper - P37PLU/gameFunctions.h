#ifndef GAMEFUNCTIONS_H_INCLUDED
#define GAMEFUNCTIONS_H_INCLUDED

#include "rectangle.h"
#include "gameStates.h"
#include "texts.h"
#include <stdbool.h>

void createTiles(DinRect *DinTiles);
bool inTiles(int x, int y, int rows, int cols);
void generateBombs(int startRow, int startCol, DinRect *DinTiles);
int calculateDistance(DinRect *DinTiles, int width);
void setBombNums(int x, int y, DinRect *DinTiles);
void revealAllBombs(DinRect *DinTiles);
void findZerosAround(int x, int y, DinRect *DinTiles);
void revealTile(int x, int y, DinRect *DinTiles);
void flagTile(DinRect *DinTiles, int x, int y);
bool checkEnd(DinRect *DinTiles);


#endif
