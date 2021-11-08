#include "rectangle.h"
#include <stdbool.h>


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

void draw(DinRect *DinTiles, SDL_Renderer *renderer, SDL_Texture *images, int cellSize){
    for(int i = 0; i < DinTiles->rows; i++){
        for(int j = 0; j < DinTiles->cols; j++){
            drawTile(DinTiles->tiles[i][j], renderer, images, cellSize);
        }
    }
}
