#include "common.h"
bool oddSecond() {
    return SDL_GetTicks() % 2000 < 1000;
}


bool oddMoment() {
    return SDL_GetTicks() % 1000 < 500;
}
