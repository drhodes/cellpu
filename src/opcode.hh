#pragma once

#include <json-c/json.h>
#include <string>

using namespace std;

// {type: Opcode, val: int}
typedef enum Opcode {     
                     NOP = 0,
                     CMP = 1,
                     SWAP = 2
} Opcode;

json_object *opcodeToJson(Opcode);
Opcode jsonToOpcode(string str);
