#ifndef CELL_C
#define CELL_C

#include "cell.h"
#include "err.h"


// typedef struct {
//     int x, y, value, size;
//     bool selected, broadcasting, listening;
//     int dataReg, colReg, rowReg;
//     int op; // this will be of type Instruction soon.
// } Cell;


Cell* newCell(int x, int y) {
    Cell *cell = (Cell*)calloc(sizeof(Cell), 1);
    cell->x = x;
    cell->y = y;
    cell->size = 60;
    return cell;
}


// self.select = function()
//    self.selected = true
// end

// self.deselect = function()
//    self.selected = false
// end

// self.setBroadcast = function(bool)
//    self.broadcasting = bool
//    self.listening = not bool
// end

// self.setListen = function(bool)
//    self.listening = bool
//    self.broadcasting = not bool
// end


// self.borderColor = function()
//    if self.selected then
//       return {0x30, 0x40, 0xFF, 0xFF}
//    else 
//       return {0x00, 0x00, 0x00, 0xFF}
//    end
// end

SDL_Color cellColor(Cell *cell) {
    // change this.
    SDL_Color c = {0x56, 0x56, 0x56, 0xFF};
    return c;
}


SDL_Color cellBorderColor(Cell *cell) {
    if (cell->selected) {
        SDL_Color c = {0x30, 0x40, 0xFF, 0xFF};
        return c;
    } else {
        SDL_Color c = {0x00, 0x00, 0x00, 0xFF};
        return c;
    }
}


// self.SWAPDR = function()
//    tmp = self.rowReg
//    self.rowReg = self.data
//    self.data = tmp
// end

void borderBox(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color border, SDL_Color fill) {
    SDL_Rect rect = {x, y, h, w};
    SDL_SetRenderDrawColor(renderer, border.r, border.g, border.b, border.a);
    SDL_RenderFillRect(renderer, &rect);
    rect.x++;
    rect.y++;
    rect.h--;
    rect.w--;
    SDL_SetRenderDrawColor(renderer, fill.r, fill.g, fill.b, fill.a);
    SDL_RenderFillRect(renderer, &rect);
}

void drawText(SDL_Renderer *renderer, Atlas *atlas, int x, int y, const char* txt) {
    SDL_Rect msgRect = { x, y, atlas->surfWidth, atlas->surfHeight };

    for (int i=0; txt[i]; i++) {
        SDL_Texture* glyph = atlasGetGlyph(atlas, txt[i]);
        nullDieMsg(glyph, "failed to get a glyph in termRender");            
        SDL_RenderCopy(renderer, glyph, NULL, &msgRect);
        msgRect.x += atlas->surfWidth;
    }
}


/*
void cellRender(Cell *cell) {
        drawText(self.x * self.size + 4,
               self.y * self.size + 4,
               "[" .. tostring(self.x) .. " " .. tostring(self.y) .. "]")
      
      drawText(self.x * self.size + 4,
               self.y * self.size + 16,
               self.op.name)
      
      drawText(self.x * self.size + self.size / 2,
               self.y * self.size + self.size / 2,
               tostring(self.data))
      
      drawText(self.x * self.size + self.size / 2 + self.size/4,
               self.y * self.size + self.size / 2,
               tostring(self.rowReg))
      
      drawText(self.x * self.size + self.size / 2,
               self.y * self.size + self.size / 2 + self.size/4,
               tostring(self.colReg))
   end

*/


void cellRender(Cell *cell, Atlas *atlas, SDL_Renderer *renderer) {
    int x = cell->x;
    int y = cell->y;
    int size = cell->size;
    int n = 0;
    
    borderBox(renderer, x * size, y * size, size, size, cellBorderColor(cell), cellColor(cell));
    char str[255]; // plenty of space.
    
    memset(str, '\0', 255);
    n = sprintf(str, "[%d %d]", x, y);
    drawText(renderer, atlas, x * size + 4, y * size + 4, str);
    
    // drawText(self.x * self.size + 4,
    //          self.y * self.size + 16,
    //          self.op.name)
    memset(str, '\0', n);
    n = sprintf(str, "%s", "OPNAME");
    drawText(renderer, atlas,
             x * size + 4,
             y * size + 16, str);

    // drawText(self.x * self.size + self.size / 2,
    //          self.y * self.size + self.size / 2,
    //          tostring(self.data))
    memset(str, '\0', n);
    n = sprintf(str, "%d", cell->dataReg);
    drawText(renderer, atlas, x * size + size/2, y * size + size/2, str);
      
    // drawText(self.x * self.size + self.size / 2 + self.size/4,
    //          self.y * self.size + self.size / 2,
    //          tostring(self.rowReg))
    memset(str, '\0', n);
    n = sprintf(str, "%d", cell->rowReg);
    drawText(renderer, atlas,
             x * size + size/2 + size/4,
             y * size + size/2, str);
      
    // drawText(self.x * self.size + self.size / 2,
    //          self.y * self.size + self.size / 2 + self.size/4,
    //          tostring(self.colReg))
    memset(str, '\0', n);
    n = sprintf(str, "%d", cell->colReg); 
    drawText(renderer, atlas,
             x * size + size/2,
             y * size + size/2 + size/4, str);
    

    
}

#endif // CELL_C
