#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdio.h>

#include "gameStates.h"
#include "rectangle.h"
#include "gameFuncTions.h"
#include "images.h"
#include "buttons.h"
#include "texts.h"
#include "game.h"
#include "default_values.h"



void initSDL(char const *title, int width, int height, SDL_Window **window, SDL_Renderer **renderer);
void startGraphics();
static void background(SDL_Color c);
//void render();
void run();
void renderMenu(Button *buttons, int size, Text title);
void renderGame(DinRect *DinTiles, SDL_Texture *images, Button *buttons, int size, Text timer, Text flags);
void renderOptions(Button *buttons, int size, Text optionsTitle);
#endif
