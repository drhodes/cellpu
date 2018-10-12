#ifndef ATLAS_H
#define ATLAS_H

#include <stdbool.h> 

#define ATLAS_SIZE 256

typedef struct {
    SDL_Texture* table[ATLAS_SIZE];
    int surfWidth, surfHeight;
} Atlas;

Atlas *newAtlas();
SDL_Texture *atlasGetGlyph(Atlas*, char);

void freeAtlas(Atlas*);


#endif // ATLAS

