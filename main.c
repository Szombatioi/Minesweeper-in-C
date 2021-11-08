#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_image.h>
#include <math.h>

#include "grafika.h"
#include "rectangle.h"
#include "gameFunctions.h"
#include "gameStates.h"
#include "setGameModes.h"
#include "debugmalloc.h"

//kezdő:    8*8   mező   10 aknával
//haladó:   16*16 mező   40 aknával
//mester:   30*16 mező   99 aknával

int main(int argc, char *argv[]){
    srand(time(0));

    SDL_Window *window;                         //a program ablaka
    SDL_Renderer *renderer;                     //a grafikus renderelõ
    int width = 800, height = 600;              //ablak szélessége, magassága
    initSDL(&window, width, height, &renderer); //a grafika inicializálása
    SDL_Event ev;                               //eseményvezérlés kezdete
    SDL_Texture *images = IMG_LoadTexture(renderer, "images_small.png"); //képek importálása

    STATE GameState = Game;                     //az alapnézet a menü
    bool running = true;                        //fut a program?

    bool inGame;                                //tart a játék?
    bool generated;                             //generált már bombákat?
    int row, col;                               //kezdeti oszlop és sorszám
    int bombNum;                                //bombák száma
    int flagNum;                                //hátralévő elérhető zászlók száma
    int falseFlags;                             //nem-aknák megjelölése

    double cellSize = 20;                       //cella mérete
    //double distance = 100;                      //játéktér távolsága az ablak szélétõl


    int startingRow, startingCol;               //elsõ kattintás helye
    int mouseX, mouseY;                         //kattintás helye

    //Button newGame;

    setup(&generated, &inGame, &row, 8, &col, 8, &bombNum, &flagNum,15); //alapértelmezett nehézség: könnyű
    //FONTOS
    //setup-ba kerüljön be DinTiles (malloc és értékadás)

    Rect **tiles;
    DinRect DinTiles = {tiles, row, col};

    DinTiles.tiles = (Rect**) malloc(DinTiles.rows * sizeof(Rect*));
    for(int i = 0; i < DinTiles.rows; i++){
        DinTiles.tiles[i] = (Rect*) malloc(DinTiles.cols * sizeof(Rect));
    }

    for(int i = 0; i < DinTiles.rows; i++){
        for(int j = 0; j < DinTiles.cols; j++){
            DinTiles.tiles[i][j] = (Rect){i*cellSize, j*cellSize, cellSize, false, false, false, false, false, 0};
        }
    }

    while(running) {
        SDL_WaitEvent(&ev);
        switch(ev.type) {
        case SDL_QUIT:
            running = false;
            SDL_Quit();
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseX = ev.motion.x/cellSize, mouseY = ev.motion.y/cellSize;

            if(GameState == Game){
                if(inTiles(mouseX, mouseY, DinTiles.rows, DinTiles.cols) && inGame){
                    if(ev.button.button == SDL_BUTTON_LEFT ){

                        if(!generated){
                            startingRow = mouseX;
                            startingCol = mouseY;
                            generateBombs(startingRow, startingCol, bombNum, &DinTiles);
                            generated = true;

                            for(int i = 0; i < DinTiles.rows; i++){
                                for(int j = 0; j < DinTiles.cols; j++){
                                    setBombNums(i, j, &DinTiles);   //minden cella körül megnézzük, hogy bomba van-e körülötte
                                }
                            }
                        }

                        if (!DinTiles.tiles[mouseX][mouseY].show && !DinTiles.tiles[mouseX][mouseY].isFlagged){
                            revealTile(mouseX, mouseY, &DinTiles, &inGame);
                        }
                    }

                    else if(ev.button.button == SDL_BUTTON_RIGHT){
                        //flagTile()
                        if(flagNum>0 && !DinTiles.tiles[mouseX][mouseY].isFlagged){
                            DinTiles.tiles[mouseX][mouseY].isFlagged = true;
                            flagNum--;
                        }
                        else if(flagNum <= bombNum && DinTiles.tiles[mouseX][mouseY].isFlagged){
                            DinTiles.tiles[mouseX][mouseY].isFlagged = false;
                            flagNum++;
                        }
                        //írja ki a flagNum-ot!


                        //activeBombs--;
                        //falseToggleOfFlag
                    }
                }
            }

        default:
            setWallpaper(renderer, 200, 200, 200, width, height);
            draw(&DinTiles, renderer, images, cellSize);
            if(!inGame){
                //setup(&generated, &inGame, &row, 8, &col, 8, &bombNum, 20, tiles, cellSize);
            }
            SDL_RenderPresent(renderer);
            break;
        }
    }


    for(int i = 0; i < row; i++){
        free(DinTiles.tiles[i]);
    }
    free(DinTiles.tiles);
    return 0;
}



