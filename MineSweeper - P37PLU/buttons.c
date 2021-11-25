#include "buttons.h"

void drawBtn(SDL_Renderer *renderer, Button const btn){
    boxRGBA(renderer, btn.x - btn.w/2, btn.y - btn.h/2, btn.x + btn.w/2, btn.y + btn.h/2, btn.bg.r, btn.bg.g, btn.bg.b, btn.bg.a);
    rectangleRGBA(renderer, btn.x - btn.w/2, btn.y - btn.h/2, btn.x + btn.w/2, btn.y + btn.h/2, btn.fg.r, btn.fg.g, btn.fg.b, btn.fg.a);
    SDL_RenderCopy(renderer, btn.text.texture, NULL, &btn.text.place);
}

bool isOver(Button btn, SDL_Event ev){
    return (ev.motion.x >= btn.x-btn.w/2) && (ev.motion.x < btn.x+btn.w/2) && (ev.motion.y >= btn.y-btn.h/2) && (ev.motion.y < btn.y+btn.h/2);
}

Button createButton(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color fg, SDL_Color bg, TTF_Font *font, char *title){
    Button b = {x,y,w,h,fg,bg};
    b.text = createText(renderer, font, title, b.x, b.y, fg, 1, false);
    return b;
}

Buttons *createMenuButtons(SDL_Renderer *renderer, int w, int h, Fonts fonts){
    Button *buttons = malloc(4 * sizeof(Button));
    buttons[0] = createButton(renderer, WIDTH/2, 150, w, h, black, dark_grey, fonts.arial32, "Play");
    buttons[1] = createButton(renderer, WIDTH/2, 150+1.5*h, w, h, black, dark_grey, fonts.arial32, "Options");
    buttons[2] = createButton(renderer, WIDTH/2, 150+3*h, w, h, black, dark_grey, fonts.arial32, "Ranklist");
    buttons[3] = createButton(renderer, WIDTH/2, 150+4.5*h, w, h, black, dark_grey, fonts.arial32, "Exit");
    return buttons;
}

Buttons *createGameButtons(SDL_Renderer *renderer, int w, int h, Fonts fonts){
    Button *buttons = malloc(4 * sizeof(Button));
    buttons[0] = createButton(renderer, 53, 30, w, h, black, dark_grey, fonts.arial24, "New");
    buttons[1] = createButton(renderer, 53, 30 + 1.5*h, w, h, black, dark_grey, fonts.arial24, "Menu");
    buttons[2] = createButton(renderer, 53, 30 + 3*h, w, h, black, dark_grey, fonts.arial24, "Pause");
    return buttons;
}

Buttons *createOptionsButtons(SDL_Renderer *renderer, int w, int h, Fonts fonts){
    Button *buttons = malloc(5 * sizeof(Button));
    buttons[0] = createButton(renderer, WIDTH/2, HEIGHT-h, w, h, black, dark_grey, fonts.arial32, "Menu");
    buttons[1] = createButton(renderer, WIDTH/2 - (3*w/4), 150, w, h, black, dark_grey, fonts.arial32, "Easy");
    buttons[2] = createButton(renderer, WIDTH/2 + (3*w/4), 150, w, h, black, dark_grey, fonts.arial32, "Medium");
    buttons[3] = createButton(renderer, WIDTH/2 - (3*w/4), 150 + 1.5*h, w, h, black, dark_grey, fonts.arial32, "Hard");
    buttons[4] = createButton(renderer, WIDTH/2 + (3*w/4), 150 + 1.5*h, w, h, black, dark_grey, fonts.arial32, "Custom");
    return buttons;
}
