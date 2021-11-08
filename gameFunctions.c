#include <stdbool.h>
#include "gameFunctions.h"


//Használat: megnézi, hogy a kattintás helye a játéktéren belül van-e.
bool inTiles(int x, int y, int rows, int cols){
    return (x>=0 && x < rows && y>=0 && y<cols);
}


int bombsAroundTooMuch(int x, int y, int rows, int cols, Rect **tiles){
    int bombs = 0;
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if(inTiles(i,j,rows,cols) && tiles[i][j].isBomb)
                bombs++;
        }
    }
    return bombs;
}


/*
    Függvény használata: az adott kezdõ sor- és oszlopszámon kívül véletlenszerûen elhelyez bombNum db bombát
    Mûködése: x és y random számok 0 és sor/oszlopszám között, bombNum-szor végigfut a függvény, és ha az adott random cella nem a kezdõkattintás helye,
    akkor lerak egy bombát, máskülönben a számlálót csökkenti, hogy ne maradjon ki bomba.
*/
void generateBombs(int startRow, int startCol, int bombNum, DinRect *DinTiles){ //pointer kell a tömbre?
    int x, y; //egy random cella
    for(int i = 0; i < bombNum; i++){
        x = rand() % DinTiles->rows; //0->rows
        y = rand() % DinTiles->cols; //0->cols
        if(DinTiles->tiles[x][y].isBomb || (x == startRow && y == startCol)){
            i--;
        }

        else
            DinTiles->tiles[x][y].isBomb = true;
    }
}


void changeTileNumber(DinRect *DinTiles, int newRow, int newCol, int cellSize){
//    if(DinTiles->tiles != NULL){
//        for(int i = 0; i < DinTiles->rows; i++){
//            free(tiles[i]);
//        }
//        free(tiles);
//    }

    DinTiles->tiles = (Rect**) malloc(newRow * sizeof(Rect*));
    for(int i = 0; i < newRow; i++){
        DinTiles->tiles[i] = (Rect*) malloc(newCol * sizeof(Rect));
    }

    DinTiles->rows = newRow;
    DinTiles->cols = newCol;

    for(int i = 0; i < DinTiles->rows; i++){
        for(int j = 0; j < DinTiles->cols; j++){
            DinTiles->tiles[i][j] = (Rect){i*cellSize, j*cellSize, cellSize, false, false, false, false, false, 0};
        }
    }
}



void calculateDistance(DinRect *DinTiles, double *distance, double cellSize, int width){
    double tilesLength = 0;
    for(int i = 0; i < DinTiles->rows; i++){
        tilesLength += cellSize;
    }
    *distance = width/2 - tilesLength/2;
}



/*
    Alapértékeket állít be a következő adatoknak:
    generálva van-e bomba? Nem
    mezők sor- és oszlopszáma
    bombák száma
*/
void setup(bool *generated, bool *inGame, int *row, int rowNum, int *col, int colNum, int *bombNum, int *flagNum, int bombs){
    *generated = false;
    *inGame = true;
    *row = rowNum;
    *col = colNum;
    *bombNum = bombs;
    *flagNum = bombs;
}

//Haszna: megszámolja egy (x,y) koordinátájú cella körül a bombák számát és eltárolja
void setBombNums(int x, int y, DinRect *DinTiles){
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if(inTiles(i, j, DinTiles->rows, DinTiles->cols) && DinTiles->tiles[i][j].isBomb){
                DinTiles->tiles[x][y].bombsAround++;
            }
        }
    }
}

//Haszna: a játék végén az összes cellát felfedi
void revealAllBombs(DinRect *DinTiles){
    //for ciklusban megjelölni a false flageket
    for(int i = 0; i < DinTiles->rows; i++)
        for(int j = 0; j < DinTiles->cols; j++)
            DinTiles->tiles[i][j].show = true;
}

void findZerosAround(int x, int y, DinRect *DinTiles){
    if(inTiles(x,y,DinTiles->rows,DinTiles->cols) && !DinTiles->tiles[x][y].show && !DinTiles->tiles[x][y].isBomb && !DinTiles->tiles[x][y].isFlagged){
        DinTiles->tiles[x][y].show = true;
        if(DinTiles->tiles[x][y].bombsAround < 2){
            findZerosAround(x-1, y, DinTiles);
            findZerosAround(x+1, y, DinTiles);
            findZerosAround(x, y-1, DinTiles);
            findZerosAround(x, y+1, DinTiles);
        }
    }
}

void revealTile(int x, int y, DinRect *DinTiles, bool *inGame){
    if(DinTiles->tiles[x][y].isBomb){
        DinTiles->tiles[x][y].firstBomb = true;
        revealAllBombs(DinTiles);
        *inGame = false;
    }
    else if(!DinTiles->tiles[x][y].isFlagged){
        if(DinTiles->tiles[x][y].bombsAround < 2){
            findZerosAround(x,y,DinTiles);
        }
        else{
            DinTiles->tiles[x][y].show = true;
        }
    }
}



void flagTile(DinRect *DinTiles, int x, int y, int *flagNum, int bombNum){
    if(!DinTiles->tiles[x][y].show){
        if(*flagNum >= 0 && !DinTiles->tiles[x][y].isFlagged){
            DinTiles->tiles[x][y].isFlagged = true;
            if(!DinTiles->tiles[x][y].isBomb){
                DinTiles->tiles[x][y].falseFlagged = true;
            }
            (*flagNum)--;
        }
        else if(*flagNum <= bombNum && DinTiles->tiles[x][y].isFlagged){
            DinTiles->tiles[x][y].isFlagged = false;
            if(DinTiles->tiles[x][y].falseFlagged){
                DinTiles->tiles[x][y].falseFlagged = false;
            }
            (*flagNum)++;
        }
    }
}
