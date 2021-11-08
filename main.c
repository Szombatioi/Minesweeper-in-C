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

enum {width = 800, height = 600, cellSize = 20};//ablak szélessége, magassága, egy cella mérete



int main(int argc, char *argv[]){
    srand(time(0));

    SDL_Window *window;                         //a program ablaka
    SDL_Renderer *renderer;                     //a grafikus renderelő
    initSDL(&window, width, height, &renderer); //a grafika inicializálása
    SDL_Event ev;                               //eseményvezérlés kezdete
    SDL_Texture *images = IMG_LoadTexture(renderer, "images_small.png"); //képek importálása
    if(images == NULL){
        printf("%s", SDL_GetError());
        exit(1);
    }

    STATE GameState = Game;                     //az alapnézet a menü
    bool running = true;                        //fut a program?

    bool inGame;                                //tart a játék?
    bool generated;                             //generált már bombákat?
    int row, col;                               //kezdeti oszlop és sorszám
    int bombNum;                                //bombák száma
    int flagNum;                                //hátralévő elérhető zászlók száma
    int falseFlags;                             //nem-aknák megjelölése

    double distance;                      //játéktér távolsága az ablak szélétõl


    int startingRow, startingCol;               //elsõ kattintás helye
    int mouseX, mouseY;                         //kattintás helye

    int tilesHidden;                            //a még fel nem fedett mezők
    //int falseFlags

    //Button newGame;





    setup(&generated, &inGame, &row, 15, &col, 8, &bombNum, &flagNum, 10); //alapértelmezett nehézség: könnyű


    Rect **tiles = (Rect**) malloc(row * sizeof(Rect*));
    if(tiles == NULL){
        printf("%s", SDL_GetError());
        exit(1);
    }

    for(int i = 0; i < row; i++){
        tiles[i] = (Rect*) malloc(col * sizeof(Rect));
        if(tiles[i] == NULL){
            printf("%s", SDL_GetError());
            exit(1);
        }
    }


    DinRect DinTiles = {tiles, row, col};


    calculateDistance(&DinTiles, &distance, cellSize, width);


    for(int i = 0; i < DinTiles.rows; i++){
        for(int j = 0; j < DinTiles.cols; j++){
            DinTiles.tiles[i][j] = (Rect){distance + i*cellSize, j*cellSize, cellSize, false, false, false, false, false, 0};
        }
    }



    while(running) {
        SDL_WaitEvent(&ev);
        switch(ev.type) {
        case SDL_QUIT:
            running = false;
            SDL_Quit();
            break;
//        case WIN:
//            //goto win screen
//            //print win
//            break;

        case SDL_MOUSEBUTTONDOWN:
            if(GameState == Game){
                mouseX = (ev.motion.x - distance)/cellSize, mouseY = ev.motion.y/cellSize;
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
                            flagTile(&DinTiles, mouseX, mouseY, &flagNum, bombNum);
                            //írja ki a flagNum-ot!


                            //activeBombs--;
                            //falseToggleOfFlag
                        }
                    }
                }
            }

        default:
            setWallpaper(renderer, 200, 200, 200, width, height);
            draw(&DinTiles, renderer, images, cellSize);
            if(!inGame){
//                setup(&generated, &inGame, &row, 8, &col, 8, &bombNum, &flagNum, 10);
//                changeTileNumber(&DinTiles, row, col, cellSize);
            }
            SDL_RenderPresent(renderer);
            break;
        }
    }


    for(int i = 0; i < DinTiles.rows; i++){
        free(tiles[i]);
    }
    free(tiles);
    return 0;
}



