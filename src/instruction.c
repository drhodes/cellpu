#include "instruction.h"
#include "err.h"

// function NOP()
//    local f = function(x)
//       return x
//    end   
//    return Instruction("NOP", f, {0x30, 0x30, 0x30, 0xFF})
// end

static void
opNOP(Grid *grid) {
    // nop doesn't do anything.
}


Instruction*
instEmpty() {
    Instruction *inst = (Instruction*)calloc(sizeof(Instruction), 1);
    return inst;
}

Instruction*
NOP() {
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
opCMPLE(Grid* grid) {
    
}

Instruction*
CMPLE(Way heading) {
    Instruction *inst = instEmpty();
    strcpy(inst->name, "CMPLE");
    inst->color = (SDL_Color){0x30, 0xAA, 0x30, 0xFF};
    inst->op = opCMPLE;
    inst->heading = heading;
    return inst;
}


void freeInstruction(Instruction* inst) {
    
    free(inst);
}
