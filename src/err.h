#ifndef ERR_H
#define ERR_H

#include <stdlib.h>
#include <stdio.h>

// global error stack.

typedef struct Err {
    const char *msg;
    char *file;
    int line;    
    const char *func;
} Err;

typedef struct ErrorStack {
    Err e;
    struct ErrorStack *next;
} ErrorStack;


// -------------------------------------------------------------------------------------------------
// GLOBAL error stack.

// TODO improve perr to accept var args
    
#define perr(errmsg) {                                                                             \
        Err e = { .msg = errmsg, .file = __FILE__, .line = __LINE__, .func = "__FUNCTION__" };     \
        pushErr(e);                                                                                \
    };

#define nullDieMsg(ptr, msg) { if (ptr==NULL) { perr(msg); dumpStack(); } }
#define nullDie(ptr) { nullDieMsg(ptr, "got null pointer"); }

#define die(msg) { perr(msg); dumpStack(); exit(1); }

void pushErr(Err e);
void dumpStack();
const char* errTopMsg();


#endif // ERR_H
