#ifndef OPCODE_H
#define OPCODE_H

#include <json-c/json.h>

// {type: Opcode, val: int}
typedef enum Opcode {     
                     NOP = 0,
                     CMP = 1,
                     SWAP = 2
} Opcode;



json_object *opcodeToJson(Opcode);
Opcode jsonToOpcode();

#endif // OPCODE_H
