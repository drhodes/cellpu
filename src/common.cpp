#include "common.h"
#include "err.h"

bool
oddSecond() {
    return SDL_GetTicks() % 2000 < 1000;
}

bool
oddMoment() {
    return SDL_GetTicks() % 1000 < 500;
}

char
headingToChar(Way w) {
    switch(w) {
    case N: return 'N';
    case E: return 'E';
    case S: return 'S';
    case W: return 'W';
    default: return '?';
    }
}

// cells don't flip over, they only rotate.
Way
wayFromHeading(Way heading, Dir dir) {
    switch(heading) {
    case N: {
        switch(dir) {
        case L: return W;
        case R: return E;
        case F: return N;
        case B: return S;
        }
    }
    case S: {
        switch(dir) {
        case L: return E;
        case R: return W;
        case F: return S;
        case B: return N;
        }
    }
    case E: {
        switch(dir) {
        case L: return N;
        case R: return S;
        case F: return E;
        case B: return W;
        }
    }
    case W: {
        switch(dir) {
        case L: return S;
        case R: return N;
        case F: return W;
        case B: return E;
        }
    }}
    die("bad code path");
}
