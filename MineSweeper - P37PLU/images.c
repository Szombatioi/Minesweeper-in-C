#include "images.h"

SDL_Texture *createImage(SDL_Renderer *renderer, char *name){
    SDL_Texture *images = IMG_LoadTexture(renderer, name); //képek importálása
    if(images == NULL){
        SDL_Log("%s", SDL_GetError());
        exit(1);
    }
    return images;
}
