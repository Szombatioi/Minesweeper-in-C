#include "game.h"

int getBombNum(Diff d){
    return ((double)d.rows*d.cols/100)*d.bombChance;
}

void setup(DinRect *DinTiles, Diff difficulty){
    int bombNum = getBombNum(difficulty);
    gameSet newGame = {.inGame = false, .generated = false, .paused=false, .rows = difficulty.rows, .cols = difficulty.cols, .bombNum = bombNum, .flagNum = bombNum, .falseFlags = 0, .tilesLeft = difficulty.rows*difficulty.cols, .bombsNotFlagged = bombNum};
    newGame.timer = (Timer){0, 0};
    DinTiles->gameSet = newGame;
}

void exitGame(DinRect *DinTiles, SDL_TimerID *timer, SDL_TimerID *ticker, SDL_Texture *images, Fonts fonts){
    SDL_RemoveTimer(*timer);
    SDL_RemoveTimer(*ticker);
    freeTiles(DinTiles);
    SDL_DestroyTexture(images);
    TTF_CloseFont(fonts.arial24);
    TTF_CloseFont(fonts.arial32);
    TTF_CloseFont(fonts.arial64);
    TTF_CloseFont(fonts.segment);
    SDL_Quit();
}

void startGame(DinRect *DinTiles, STATE *GameState, Diff difficulty, int w){
    if(DinTiles->tiles == NULL)
        mallocTiles(DinTiles, difficulty.rows, difficulty.cols);
    else{
        if(difficulty.rows != DinTiles->gameSet.rows || difficulty.cols != DinTiles->gameSet.cols){
            freeTiles(DinTiles);
            mallocTiles(DinTiles, difficulty.rows, difficulty.cols);
        }
    }
    setup(DinTiles, difficulty);
    DinTiles->gameSet.distance = calculateDistance(DinTiles, w);
    createTiles(DinTiles);
    *GameState = GAME;
}

void clicked(DinRect *DinTiles, int clickX, int clickY, SDL_Event ev){
    if(ev.button.button == SDL_BUTTON_LEFT){
        if(!DinTiles->gameSet.generated){
            DinTiles->gameSet.inGame = true;
            generateBombs(clickX, clickY, DinTiles);

            for(int i = 0; i < DinTiles->gameSet.cols; i++){
                for(int j = 0; j < DinTiles->gameSet.rows; j++){
                    setBombNums(i, j, DinTiles);   //minden cella körül megnézzük, hogy bomba van-e körülötte
                }
            }
        }
        if (DinTiles->gameSet.inGame && !DinTiles->tiles[clickX][clickY].show && !DinTiles->tiles[clickX][clickY].isFlagged){
            revealTile(clickX, clickY, DinTiles);
        }
    }
    else if(ev.button.button == SDL_BUTTON_RIGHT && !DinTiles->gameSet.paused){
        flagTile(DinTiles, clickX, clickY);

    }
}

void changeDiff(Diff *difficulty, Diff newDifficulty){
    *difficulty = newDifficulty;
}
