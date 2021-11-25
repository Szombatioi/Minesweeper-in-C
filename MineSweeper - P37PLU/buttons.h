#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include "texts.h"
#include "gameStates.h"
#include "default_values.h"
typedef struct {
    int x, y, w, h;
    SDL_Color fg, bg;
    Text text;
} Button;

typedef struct{
    int menuBtnNum;
    Button *menuButtons;
    int gameBtnNum;
    Button *gameButtons;

} Buttons;

void drawBtn(SDL_Renderer *renderer, Button const btn);
bool isOver(Button btn, SDL_Event ev);
Button createButton(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color fg, SDL_Color bg, TTF_Font *font, char *title);
Buttons *createMenuButtons(SDL_Renderer *renderer, int w, int h, Fonts fonts);
Buttons *createGameButtons(SDL_Renderer *renderer, int w, int h, Fonts fonts);

#endif
