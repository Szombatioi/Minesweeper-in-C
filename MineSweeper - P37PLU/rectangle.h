#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED
#include <stdbool.h>
#include <stdlib.h>
#include <SDL.h>
#include "default_values.h"

typedef struct{
    int x,y,bombsAround;
    bool isBomb, show, isFlagged, firstBomb, falseFlagged;
} Rect;

typedef struct{
    bool inGame, generated, paused;
    int rows, cols, bombNum, flagNum, falseFlags, distance, tilesLeft, bombsNotFlagged;
    Timer timer;
} gameSet;

typedef struct {
    Rect **tiles;
    int cellSize;
    gameSet gameSet;
} DinRect;



void freeTiles(DinRect *DinTiles);
void mallocTiles(DinRect *DinTiles, int row, int col);
SDL_Rect source(int which, int cellSize);
SDL_Rect dest(int x, int y, int cellSize);
void drawTile(Rect const r, SDL_Renderer *renderer, SDL_Texture *images, int cellSize);
void draw(DinRect *DinTiles, SDL_Renderer *renderer, SDL_Texture *images);

#endif
