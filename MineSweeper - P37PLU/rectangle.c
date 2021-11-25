#include "rectangle.h"
#include "debugmalloc.h"

void freeTiles(DinRect *DinTiles){
    for(int i = 0; i < DinTiles->gameSet.cols; i++)
        free(DinTiles->tiles[i]);
    free(DinTiles->tiles);
}

void mallocTiles(DinRect *DinTiles, int row, int col){
    Rect **newTiles = (Rect**) malloc(col * sizeof(Rect*));
    for(int i = 0; i < col; i++)
        newTiles[i] = (Rect*) malloc(row * sizeof(Rect));
    if(DinTiles->tiles == NULL)
        freeTiles(DinTiles);
    DinTiles->tiles = newTiles;
}

SDL_Rect source(int which, int cellSize){
    int x = cellSize*(which-1); //1. kép esetén 0*20 = 0. pixeltõl
    SDL_Rect s = {x, 0, cellSize, cellSize};
    return s;
}

SDL_Rect dest(int x, int y, int cellSize){
    SDL_Rect d = {x, y, cellSize, cellSize};
    return d;
}

void drawTile(Rect const r, SDL_Renderer *renderer, SDL_Texture *images, int cellSize){
    SDL_Rect s, d = dest(r.x, r.y, cellSize);
    if(!r.show){
        //tile, flag
        if(r.isFlagged){
            s = source(11, cellSize);
        }
        else{
            s = source(10, cellSize);
        }
    }
    else{ //if(r.show)
        if(r.falseFlagged){
            s = source(12, cellSize);
        }
        else if(!r.falseFlagged && r.isFlagged){
            s = source(11, cellSize);
        }
        else{
            if(r.firstBomb){
                s = source(14, cellSize);
            }
            else if(!r.firstBomb && r.isBomb){
                s = source(13, cellSize);
            }
            else{
                s = source(r.bombsAround+1, cellSize);
            }
        }
    }
    SDL_RenderCopy(renderer, images, &s, &d);
}

void draw(DinRect *DinTiles, SDL_Renderer *renderer, SDL_Texture *images){
    for(int i = 0; i < DinTiles->gameSet.cols; i++){
        for(int j = 0; j < DinTiles->gameSet.rows; j++){
            drawTile(DinTiles->tiles[i][j], renderer, images, DinTiles->cellSize);
        }
    }
}

