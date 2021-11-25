#include <SDL.h>
#include "graphics.h"
#include <stdbool.h>
#include "time.h"
#include "debugmalloc.h"

int main(int argc, char *argv[]) {
    srand(time(0));
    startGraphics();
    run();
    return 0;
}
