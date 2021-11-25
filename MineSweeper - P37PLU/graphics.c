#include "graphics.h"
static SDL_Window *window;
static SDL_Renderer *renderer;
static Diff easy = {8, 8, 15}, medium = {16, 16, 15}, hard = {32, 32, 20};



/**
 * A függvény létrehozza az ablakot és a megjelenítőt
 * @param title, az ablak címe
 * @param width, height az ablak szélessége, magassága
 * @param window, az ablakunkra mutató pointer, amit cím szerint változtatunk meg
 * @param renderer, a megjelenítőre mutató pointer, amit cím szerint változtatunk meg
 */
void initSDL(char const *title, int width, int height, SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("%s", SDL_GetError());
        exit(1);
    }
    SDL_Window *Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == NULL) {
        SDL_Log("%s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("%s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(Renderer);

    *window = Window;
    *renderer = Renderer;
}

/**
 * Ez a függvény teszi elérhetővé a main függvényben az SDL inicializálását
*/
void startGraphics(){
    initSDL("MineSweeper", WIDTH, HEIGHT, &window, &renderer);
}

/**
 * Ezzel a függvénnyel egy tetszőleges színű hátteret lehet kirajzolni a képernyőre
 * @param c, a háttér színe
*/
static void background(SDL_Color c){
    boxRGBA(renderer, 0, 0, WIDTH, HEIGHT, c.r, c.g, c.b, c.a);
}

/**
 * A beépített SDL függvény a folyamatos megjelenítés érdekében minden 100. milliszekundumban küld egy jelet a játéknak
 * @param ms, a hívás gyakorisága ms-ben
*/
Uint32 tick(Uint32 ms, void *parameter){
    SDL_Event ev;
    ev.type = RENDER;
    SDL_PushEvent(&ev);
    return ms;
}

/**
 * A beépített SDL függvény a játék idejének méréséért küld ki minden másodpercben egy jelet.
 * @param ms, a hívás gyakorisága ms-ben
*/
Uint32 TimeCounter(Uint32 ms, void *parameter){
    SDL_Event ev;
    ev.type = TIMER;
    SDL_PushEvent(&ev);
    return ms;
}

/**
 * A menü kirajzolásáért felel
 * Először a gombokat rajzolja ki, majd a címet, végül az alsó sarokban elhelyez egy megjelölést a készítőre
 * @param *buttons, tömbben eltárolt gombok, amiket ki kell rajzolni
 * @param size, a szám, ami megmondja hány elem van a buttons tömbben
 * @param title, a kiírandó játékcím
*/
void renderMenu(Button *buttons, int size, Text title){
    for(int i = 0; i < size; i++){
        drawBtn(renderer, buttons[i]);
    }
    drawText(renderer, title);
    stringRGBA(renderer, 0, HEIGHT - 10, "Created By: Oliver Szombati", 0, 0, 0, 255);
}

/**
 * Az aktuális játék kirajzolásáért felel.
 * Először a mezőket, majd a gombokat, végül az időt és a zászlók számát rajzolja ki
 * @param *DinTiles, a játékszettet tartalmazó Dinamikus Tömb
 * @param *images, a mezők kirajzolásáért felelős képek
 * @param *buttons, tömbben eltárolt gombok, amiket ki kell rajzolni
 * @param size, a szám, ami megmondja hány elem van a buttons tömbben
 * @param timer, az időt tároló struktúra
*/
void renderGame(DinRect *DinTiles, SDL_Texture *images, Button *buttons, int size, Text timer, Text flags){
    draw(DinTiles, renderer, images);
    for(int i = 0; i < size; i++){
        drawBtn(renderer, buttons[i]);
    }
    drawText(renderer, timer);
    drawText(renderer, flags);
//    SDL_RenderCopy(renderer, timer.texture, NULL, &timer.place);
//    SDL_RenderCopy(renderer, flags.texture, NULL, &flags.place);
}

/**
 * Az beállítások nézet kirajzolásáért felel.
 * Először a címet (Options), majd a gombokat rajzolja ki
 * @param *buttons, tömbben eltárolt gombok, amiket ki kell rajzolni
 * @param size, a szám, ami megmondja hány elem van a buttons tömbben
 * @param optionsTitle, a nézet címe, amit kirajzol
*/
void renderOptions(Button *buttons, int size, Text optionsTitle){
    SDL_RenderCopy(renderer, optionsTitle.texture, NULL, &optionsTitle.place);
    for(int i = 0; i < size; i++){
        drawBtn(renderer, buttons[i]);
    }
}

void renderWinScreen(Text winTitle){
    SDL_RenderCopy(renderer, winTitle.texture, NULL, &winTitle.place);
}

void gotoWinscreen(DinRect *DinTiles, SDL_Texture *images, STATE *GameState){
    draw(DinTiles, renderer, images);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    *GameState = WIN;
}

Text updateFlags(/*SDL_Renderer *renderer, */char *flagString, int flagNum, Text flags, TTF_Font *font){
    sprintf(flagString, "%03d", flagNum);
    Text newFlags = createText(renderer, font, flagString, WIDTH-10, 65, red, 2, true);
    return newFlags;
}

void run(){
    TTF_Init();
    Fonts fonts = createFonts();

    Diff difficulty = easy;
    DinRect DinTiles = {NULL, 20};

    char timerString[5+1] = "00:00";
    Text timer = createText(renderer, fonts.segment, timerString, WIDTH-10, 25, red, 2, true);

    char flagString[3+1];
    Text flags = updateFlags(flagString, DinTiles.gameSet.flagNum, flags, fonts.segment);

    Timer t = {0,0};

    Button *menuButtons = createMenuButtons(renderer, 250, 75, fonts);
    Button *gameButtons = createGameButtons(renderer, 100, 50, fonts);
    Button *optionsButtons = createOptionsButtons(renderer, 250, 75, fonts);

    Texts texts = createTexts(renderer, fonts);

    STATE GameState = MENU;
    SDL_Texture *images = createImage(renderer, "images_small.png");

    SDL_Event ev;
    int clickX, clickY;
    SDL_TimerID ticker = SDL_AddTimer(100, tick, NULL);
    SDL_TimerID timeCounter = SDL_AddTimer(1000, TimeCounter, NULL);

    while(SDL_WaitEvent(&ev) == 1) {
        switch(ev.type) {

        //ha az X-re kattintunk
        case SDL_QUIT:
            /*******************************************************************************/
            /*******************************************************************************/
            /*******************************************************************************/
            free(gameButtons);
            free(menuButtons); //másik helyen is rossz
            free(optionsButtons);
            /*******************************************************************************/
            /*******************************************************************************/
            /*******************************************************************************/
            exitGame(&DinTiles, &ticker, &timeCounter, images, fonts);
            break;


        //ha megnyomjuk a gombot (felemelésre aktiválódik, téves kattintás kijavítására jó)
        case SDL_MOUSEBUTTONUP:
            clickX = (ev.motion.x - DinTiles.gameSet.distance)/DinTiles.cellSize, clickY = ev.motion.y/DinTiles.cellSize;
            if(GameState == GAME){
                if(inTiles(clickX, clickY, DinTiles.gameSet.rows, DinTiles.gameSet.cols) && !DinTiles.gameSet.paused){
                    clicked(&DinTiles, clickX, clickY, ev);
                    flags = updateFlags(flagString, DinTiles.gameSet.flagNum, flags, fonts.segment);
                }
                if(checkEnd(&DinTiles)){
                    gotoWinscreen(&DinTiles, images, &GameState);
                }

                if(isOver(gameButtons[0], ev)){
                    startGame(&DinTiles, &GameState, difficulty, WIDTH);
                    flags = updateFlags(flagString, DinTiles.gameSet.flagNum, flags, fonts.segment);
                    timer = changeText(renderer, fonts.segment, "00:00", timer, red);
                }
                if(isOver(gameButtons[1], ev)){
                    GameState = MENU;
                }
                if(isOver(gameButtons[2], ev) && DinTiles.gameSet.inGame){
                    //Pause();
                    DinTiles.gameSet.paused = !DinTiles.gameSet.paused;

                }
            }

            else if(GameState == MENU){
                if(isOver(menuButtons[0], ev)){
                    startGame(&DinTiles, &GameState, difficulty, WIDTH);
                    flags = updateFlags(flagString, DinTiles.gameSet.flagNum, flags, fonts.segment);
                    timer = changeText(renderer, fonts.segment, "00:00", timer, red);
                }
                if(isOver(menuButtons[1], ev)){
                    GameState = OPTIONS;
                }
                if(isOver(menuButtons[2], ev)){
                    GameState = RANKLIST;
                }
                if(isOver(menuButtons[3], ev)){
                    /********************************************/
                    /********************************************/
                    /********************************************/
                    free(gameButtons);
                    free(menuButtons);
                    free(optionsButtons);
                    /********************************************/
                    /********************************************/
                    /********************************************/
                    exitGame(&DinTiles, &ticker, &timeCounter, images, fonts);
                }
            }
            else if(GameState == OPTIONS){
                if(isOver(optionsButtons[0], ev)){
                    GameState = MENU;
                }
                if(isOver(optionsButtons[1], ev)){
                    changeDiff(&difficulty, easy);
                }
                if(isOver(optionsButtons[2], ev)){
                    changeDiff(&difficulty, medium);
                }
                if(isOver(optionsButtons[3], ev)){
                    changeDiff(&difficulty, hard);
                }
            }
            break;


        //ha nem történik semmi küldünk egy jelet
        case RENDER:
            SDL_RenderClear(renderer);
            background(grey);
            if(GameState == MENU){
                renderMenu(menuButtons, 4, texts.title);
            }
            else if(GameState == GAME){
                if(DinTiles.gameSet.paused){
                    gameButtons[2].text = createText(renderer, fonts.arial24, "Resume", gameButtons[2].x, gameButtons[2].y, black, 1, false);
                }
                else{
                    gameButtons[2].text = createText(renderer, fonts.arial24, "Pause", gameButtons[2].x, gameButtons[2].y, black, 1, false);
                }
                renderGame(&DinTiles, images, gameButtons, 3, timer, flags);
            }
            else if(GameState == OPTIONS){
                renderOptions(optionsButtons, 5, texts.optionsTitle);
            }
            else if(GameState == WIN){
                renderWinScreen(texts.winTitle);
            }
            SDL_RenderPresent(renderer);
            break;

        case TIMER:
            /*************************************************************/
            /*************************************************************/
            /*************************************************************/
            //fv-be
            //enCount 170. sorban
            if(GameState == GAME){
                if(DinTiles.gameSet.inGame && !DinTiles.gameSet.paused)
                    countTimer(&DinTiles);
                sprintf(timerString, "%02d:%02d", DinTiles.gameSet.timer.m, DinTiles.gameSet.timer.s);
                timer = changeText(renderer, fonts.segment, timerString, timer, red);
            }

            /*************************************************************/
            /*************************************************************/
            /*************************************************************/
            break;
        }
    }
}
