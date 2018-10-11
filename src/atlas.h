#ifndef ATLAS_H
#define ATLAS_H

#include <stdbool.h> 

typedef struct {
    SDL_Texture* table[128];
    int surfWidth, surfHeight;
} Atlas;

Atlas *newAtlas();
void freeAtlas(Atlas*);



#endif // ATLAS

