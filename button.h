#ifndef BUTTON_H
#define BUTTON_H


typedef struct {
    double w, h, x, y;  //x, y ki lesz sz�m�tva relat�ven w, h-t�l (k�z�pen helyezi el)
    char *title;        //malloccal
} Button;

void clickButton(int mx, int my, Button *btn);

#endif
