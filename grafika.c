#include <SDL.h>

void initSDL(SDL_Window **Window, int width, int height, SDL_Renderer **Renderer){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("%s", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("Aknakereso", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == NULL){
        printf("%s", SDL_GetError());
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(renderer == NULL){
        printf("%s", SDL_GetError());
        exit(2);
    }

    SDL_RenderClear(renderer);

    *Window = window;
    *Renderer = renderer;
}


void setWallpaper(SDL_Renderer **renderer, int r, int g, int b, int w, int h){
    boxRGBA(renderer, 0, 0, w, h, r, g, b, 255);
}
