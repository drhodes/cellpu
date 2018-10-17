#include "err.h"
#include "instruction.h"

// function NOP()
//    local f = function(x)
//       return x
//    end   
//    return Instruction("NOP", f, {0x30, 0x30, 0x30, 0xFF})
// end

struct Instruction;

Instruction*
instEmpty() {
    Instruction *inst = (Instruction*)calloc(sizeof(Instruction), 1);
    return inst;
}

void
opNOP(struct Grid *grid, struct Cell* cell) {
    // nop doesn't do anything.
}

Instruction*
iNOP() {
    Instruction *inst = instEmpty();
    strcpy(inst->name, "NOP");
    inst->color = (SDL_Color){0x30, 0x30, 0x30, 0xFF};
    inst->op = opNOP;
    return inst;
}

// function CMPLE()
//    local f = function(x, y)
//       if x <= y then return 1 else return 0 end
//    end
//    return Instruction("CMPLE", f, {0x30, 0xAA, 0x30, 0xFF})
// end

static void
opCMPLE(struct Grid* grid, struct Cell* cell) {
    // make sure there are only two direction flags set.
    //cell->
}

Instruction*
iCMPLE() {
    Instruction *inst = instEmpty();
    strcpy(inst->name, "CMPLE");
    inst->color = (SDL_Color){0x30, 0xAA, 0x30, 0xFF};
    inst->op = opCMPLE;
    return inst;
}

void freeInstruction(Instruction* inst) {
    free(inst);
}
