#ifndef ERR_H
#define ERR_H

#include <stdlib.h>
#include <stdio.h>

// global error stack.

typedef struct Err {
    const char *msg;
    char *file;
    int line;    
} Err;

typedef struct ErrorStack {
    Err e;
    struct ErrorStack *next;
} ErrorStack;


// -------------------------------------------------------------------------------------------------
// GLOBAL error stack.

    
#define perr(errmsg) {                                                  \
        Err e = { .msg = errmsg, .file = __FILE__, .line = __LINE__ };  \
        pushErr(e);                                                     \
    };

#define nullDieMsg(ptr, msg) { if (ptr==NULL) { perr(msg); dumpStack(); } }
#define nullDie(ptr) { nullDieMsg(ptr, "got null pointer"); }


void pushErr(Err e);
void dumpStack();

#endif // ERR_H
