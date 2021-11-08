#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdbool.h>
#include <SDL.h>

typedef struct {
    double x,y,size;
    bool isBomb, show, isFlagged, firstBomb, falseFlagged;    //alapból false
    int bombsAround;                            //alapból 0
} Rect;

typedef struct{
    Rect **tiles;
    int rows, cols;
} DinRect;

SDL_Rect source(int which, int cellSize);
SDL_Rect dest(int x, int y, int cellSize);
void drawTile(Rect const r, SDL_Renderer *renderer, SDL_Texture *images, int cellSize);
void draw(DinRect *DinTiles, SDL_Renderer *renderer, SDL_Texture *images, int cellSize);


#endif
