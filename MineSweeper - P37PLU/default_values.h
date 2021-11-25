#ifndef DEFAULT_VALUES_H_INCLUDED
#define DEFAULT_VALUES_H_INCLUDED
#include <SDL.h>

enum {WIDTH = 850, HEIGHT = 600};
enum {RENDER = SDL_USEREVENT, TIMER = SDL_USEREVENT+1};
static SDL_Color grey = {200, 200, 200, 255}, dark_grey = {100, 100, 100, 255}, black = {0,0,0,255}, red = {255, 0, 0, 255};
typedef struct{
    int m, s;
} Timer;
#endif
