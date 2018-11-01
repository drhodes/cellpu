#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include "opcode.h"
#include "err.h"



// {type: Opcode, val: int}

json_object *opcodeToJson(Opcode opc) {
    json_object *obj = json_object_new_object();
    
    json_object *type = json_object_new_string("Opcode");
    json_object *num = json_object_new_int64((int)opc);


    json_object_object_add(obj, "type", type);
    json_object_object_add(obj, "value", num);
    
    printf("The json object created: %s\n", json_object_to_json_string(obj));
    
    return obj;
}


Opcode jsonToOpcode(char *str) {
    struct json_object *obj = json_tokener_parse(str); 
    nullDieMsg(obj, "Could not parse Opcode from json");
    
    struct json_object *objType = json_object_object_get(obj, "type");
    nullDieMsg(objType, "Could not find 'type' key");

    const char *typeStr = json_object_get_string(objType);
    if (strcmp(typeStr, "Opcode") != 0) {
        die("expecing type:Opcode found something else");
    }

    struct json_object *value = json_object_object_get(obj, "value");
    nullDieMsg(objType, "Could not find 'value' key");
    
    return (Opcode)json_object_get_int64(value);
}
