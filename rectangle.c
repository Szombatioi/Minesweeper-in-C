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
    if (!r.show){
        s = source(10, cellSize);
        SDL_RenderCopy(renderer, images, &s, &d);
    }

    else if (!r.isBomb && r.show) {
        s = source(r.bombsAround+1, cellSize);
        SDL_RenderCopy(renderer, images, &s, &d);


//        switch(r.bombsAround) {
//        case 0:
//        s = source(1, cellSize);
//        SDL_RenderCopy(renderer, images, &s, &d);
//        break;
//        case 1:
//        s = source(2, cellSize);
//        SDL_RenderCopy(renderer, images, &s, &d);
//        break;
//        case 2:
//        s = source(3, cellSize);
//        SDL_RenderCopy(renderer, images, &s, &d);
//        break;
//        case 3:
//        s = source(4, cellSize);
//        SDL_RenderCopy(renderer, images, &s, &d);
//        break;
//        case 4:
//        s = source(5, cellSize);
//        SDL_RenderCopy(renderer, images, &s, &d);
//        break;
//        case 5:
//        s = source(6, cellSize);
//        SDL_RenderCopy(renderer, images, &s, &d);
//        break;
//        case 6:
//        s = source(7, cellSize);
//        SDL_RenderCopy(renderer, images, &s, &d);
//        break;
//        case 7:
//        s = source(8, cellSize);
//        SDL_RenderCopy(renderer, images, &s, &d);
//        break;
//        case 8:
//        s = source(9, cellSize);
//        SDL_RenderCopy(renderer, images, &s, &d);
//        break;
//        }
      }

    else if (r.isBomb && r.show && !r.firstBomb) {//bomba és mutatjuk
        s = source(12, cellSize);
        SDL_RenderCopy(renderer, images, &s, &d);
    }
    else if(r.isBomb && r.show && r.firstBomb){
        s = source(13, cellSize);
        SDL_RenderCopy(renderer, images, &s, &d);
    }

    if(r.isFlagged && !r.show){
        s = source(11, cellSize);
        SDL_RenderCopy(renderer, images, &s, &d);
    }
}

void draw(DinRect *DinTiles, SDL_Renderer *renderer, SDL_Texture *images, int cellSize){
    for(int i = 0; i < DinTiles->rows; i++){
        for(int j = 0; j < DinTiles->cols; j++){
            drawTile(DinTiles->tiles[i][j], renderer, images, cellSize);
        }
    }
}
