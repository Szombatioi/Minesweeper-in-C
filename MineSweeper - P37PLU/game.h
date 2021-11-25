#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include "rectangle.h"
#include "gameStates.h"
#include "texts.h"


typedef struct{
    int rows, cols, bombChance;
} Diff;

int getBombNum(Diff d);
void setup(DinRect *DinTiles, Diff difficulty);
void exitGame(DinRect *DinTiles, SDL_TimerID *timer, SDL_TimerID *ticker, SDL_Texture *images, Fonts fonts);
void startGame(DinRect *DinTiles, STATE *GameState, Diff difficulty, int w);
void clicked(DinRect *DinTiles, int clickX, int clickY, SDL_Event ev);
void changeDiff(Diff *difficulty, Diff newDifficulty);
#endif
