#ifndef GRAFIKA_H
#define GRAFIKA_H

void initSDL(SDL_Window **Window, int width, int height, SDL_Renderer **Renderer);
void setWallpaper(SDL_Renderer **renderer, int r, int g, int b, int w, int h);
#endif
