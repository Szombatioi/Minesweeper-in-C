#include "texts.h"

void countTimer(DinRect *DinTiles){
    if(DinTiles->gameSet.timer.m == 99 && DinTiles->gameSet.timer.s >= 59){
        DinTiles->gameSet.inGame = false;
        revealAllBombs(DinTiles);
    }
    else{
        DinTiles->gameSet.timer.s++;
        if(DinTiles->gameSet.timer.s == 60){
            DinTiles->gameSet.timer.s = 0;
            DinTiles->gameSet.timer.m++;
        }
    }
}

void drawText(SDL_Renderer *renderer, Text text){
    if(text.bg){
        boxRGBA(renderer, text.place.x-5, text.place.y-5, text.place.x + text.place.w+5, text.place.y + text.place.h+5, 100, 100, 100, 255);
        rectangleRGBA(renderer, text.place.x-5, text.place.y-5, text.place.x + text.place.w+5, text.place.y + text.place.h+5, 0, 0, 0, 255);
    }
    SDL_RenderCopy(renderer, text.texture, NULL, &text.place);
}

Text createText(SDL_Renderer *renderer, TTF_Font *font, char *text, int x, int y, SDL_Color c, int textMode, bool bg){
    //textmode: 0 left, 1 center, 2 right
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, c);
    Text t = {.bg = bg, .textMode = textMode};
    t.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(t.textMode == 1){
        x -= surface->w/2;
    }
    else if(t.textMode == 2){
        x -= surface->w;
    }
    SDL_Rect r = {x, y-surface->h/2, surface->w, surface->h};
    t.place = r;
    SDL_FreeSurface(surface);
    return t;
}

Text changeText(SDL_Renderer *renderer, TTF_Font *font, char *text, Text te, SDL_Color c){
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, c);
    Text t;
    t.texture = SDL_CreateTextureFromSurface(renderer, surface);
    t.place = te.place;
    SDL_FreeSurface(surface);
    return t;
}

Fonts createFonts(){
    Fonts fonts;
    fonts.arial24 = TTF_OpenFont("arial.ttf", 24);
    fonts.arial32 = TTF_OpenFont("arial.ttf", 32);
    fonts.arial64 = TTF_OpenFont("arial.ttf", 64);
    fonts.segment = TTF_OpenFont("segment.ttf", 24);
    return fonts;
}

Texts createTexts(SDL_Renderer *renderer, Fonts fonts){
    Text title = createText(renderer, fonts.arial64, "MineSweeper", WIDTH/2, 50, black, 1, false);
    Text optionsTitle = createText(renderer, fonts.arial64, "Options", WIDTH/2, 50, black, 1, false);
    Text winTitle = createText(renderer, fonts.arial64, "You Won!", WIDTH/2, 50, black, 1, false);
    Texts texts = {title, optionsTitle, winTitle};
    return texts;
}

int toMinutes(int c){
    return c/60;
}

int toSeconds(int c){
    return c - (c/60)*60;
}
