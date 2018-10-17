#include "common.h"
bool oddSecond() {
    return SDL_GetTicks() % 2000 < 1000;
}
