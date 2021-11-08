#ifndef BUTTON_H
#define BUTTON_H


typedef struct {
    double w, h, x, y;  //x, y ki lesz számítva relatíven w, h-tól (középen helyezi el)
    char *title;        //malloccal
} Button;

void clickButton(int mx, int my, Button *btn);

#endif
