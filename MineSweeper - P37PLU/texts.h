#ifndef TEXTS_H_INCLUDED
#define TEXTS_H_INCLUDED
#include <SDL.h>
#include <SDL_ttf.h>
#include "rectangle.h"
#include <stdbool.h>
typedef struct {
    SDL_Texture *texture;
    SDL_Rect place;
    bool bg;
    int textMode;
} Text;

typedef struct{
    TTF_Font *arial24;
    TTF_Font *arial32;
    TTF_Font *arial64;
    TTF_Font *segment;
} Fonts;

typedef struct{
    Text title;
    Text optionsTitle;
    Text winTitle;
} Texts;

Text createText(SDL_Renderer *renderer, TTF_Font *font, char *text, int x, int y, SDL_Color c, int textMode, bool bg);
Text changeText(SDL_Renderer *renderer, TTF_Font *font, char *text, Text te, SDL_Color c);
Fonts createFonts();
Texts createTexts(SDL_Renderer *renderer, Fonts fonts);
int toMinutes(int c);
int toSeconds(int c);
#endif
