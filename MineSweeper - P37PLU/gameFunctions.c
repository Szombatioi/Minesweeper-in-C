#include "gameFunctions.h"

int calculateDistance(DinRect *DinTiles, int width){
    return width/2 - (DinTiles->gameSet.cols * DinTiles->cellSize / 2);
}

void createTiles(DinRect *DinTiles){
    for(int i = 0; i < DinTiles->gameSet.cols; i++){
        for(int j = 0; j < DinTiles->gameSet.rows; j++){
            DinTiles->tiles[i][j] = (Rect){DinTiles->gameSet.distance+(i*DinTiles->cellSize), j*DinTiles->cellSize, 0, false, false, false, false, false};
        }
    }
}


bool inTiles(int x, int y, int rows, int cols){
    return (x>=0 && x < rows && y>=0 && y<cols);
}

void generateBombs(int startRow, int startCol, DinRect *DinTiles){
    int x, y; //egy random cella
    for(int i = 0; i < DinTiles->gameSet.bombNum; i++){
        x = rand() % DinTiles->gameSet.rows; //0->rows
        y = rand() % DinTiles->gameSet.cols; //0->cols
        if(DinTiles->tiles[x][y].isBomb || (x == startRow && y == startCol)){
            i--;
        }
        else{
            DinTiles->tiles[x][y].isBomb = true;
        }

    }
    DinTiles->gameSet.generated = true;
}

void setBombNums(int x, int y, DinRect *DinTiles){
    for(int i = x-1; i <= x+1; i++){
        for(int j = y-1; j <= y+1; j++){
            if(inTiles(i, j, DinTiles->gameSet.cols, DinTiles->gameSet.rows) && DinTiles->tiles[i][j].isBomb){
                DinTiles->tiles[x][y].bombsAround++;
            }
        }
    }
}

void revealAllBombs(DinRect *DinTiles){
    //for ciklusban megjelölni a false flageket
    for(int i = 0; i < DinTiles->gameSet.cols; i++)
        for(int j = 0; j < DinTiles->gameSet.rows; j++)
            DinTiles->tiles[i][j].show = true;
}

void findZerosAround(int x, int y, DinRect *DinTiles){
    if(inTiles(x,y,DinTiles->gameSet.rows,DinTiles->gameSet.cols) && !DinTiles->tiles[x][y].show && !DinTiles->tiles[x][y].isBomb && !DinTiles->tiles[x][y].isFlagged){
        DinTiles->tiles[x][y].show = true;
        DinTiles->gameSet.tilesLeft--;
        if(DinTiles->tiles[x][y].bombsAround < 2){
            findZerosAround(x-1, y, DinTiles);
            findZerosAround(x+1, y, DinTiles);
            findZerosAround(x, y-1, DinTiles);
            findZerosAround(x, y+1, DinTiles);
        }
    }
}

void revealTile(int x, int y, DinRect *DinTiles){
    if(DinTiles->tiles[x][y].isBomb){
        DinTiles->tiles[x][y].firstBomb = true;
        revealAllBombs(DinTiles);
        DinTiles->gameSet.inGame = false;
    }
    else if(!DinTiles->tiles[x][y].isFlagged){
        if(DinTiles->tiles[x][y].bombsAround < 2){
            findZerosAround(x,y,DinTiles);
        }
        else{
            DinTiles->tiles[x][y].show = true;
            DinTiles->gameSet.tilesLeft--;
        }
    }
}

void flagTile(DinRect *DinTiles, int x, int y){
    if(!DinTiles->tiles[x][y].show){
        if(DinTiles->gameSet.flagNum > 0 && !DinTiles->tiles[x][y].isFlagged){
            DinTiles->tiles[x][y].isFlagged = true;
            if(!DinTiles->tiles[x][y].isBomb){
                DinTiles->tiles[x][y].falseFlagged = true;
            }
            else{
                DinTiles->gameSet.bombsNotFlagged--;
            }
            DinTiles->gameSet.flagNum--;
        }
        else if(DinTiles->gameSet.flagNum <= DinTiles->gameSet.bombNum && DinTiles->tiles[x][y].isFlagged){
            DinTiles->tiles[x][y].isFlagged = false;
            if(DinTiles->tiles[x][y].falseFlagged){
                DinTiles->tiles[x][y].falseFlagged = false;
            }
            else{
                DinTiles->gameSet.bombsNotFlagged++;
            }
            DinTiles->gameSet.flagNum++;
        }
    }
}

bool checkEnd(DinRect *DinTiles){
    if(DinTiles->gameSet.bombsNotFlagged == 0 || (DinTiles->gameSet.falseFlags == 0 && DinTiles->gameSet.tilesLeft <= DinTiles->gameSet.bombNum)){
        for(int i = 0; i < DinTiles->gameSet.cols; i++){
            for(int j = 0; j < DinTiles->gameSet.rows; j++){
                if(!DinTiles->tiles[i][j].isBomb && !DinTiles->tiles[i][j].show)
                    DinTiles->tiles[i][j].show = true;
            }
        }
        return true;
    }
    return false;
}
