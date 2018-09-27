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

static ErrorStack *_estack = NULL;

void pushErr(Err e) {                     
    ErrorStack *stk = (ErrorStack*)malloc(sizeof(ErrorStack));
    stk->e = e;
    stk->next = _estack;
    _estack = stk;
}
    
#define perr(errmsg) {                                                  \
        Err e = { .msg = errmsg, .file = __FILE__, .line = __LINE__ };  \
        pushErr(e);                                                     \
    };

void reportUnwind() {
    if (_estack) printf(" -- ERROR STACK --\n");
    while (_estack) {
        printf(" %s (%s, %d)\n", _estack->e.msg, _estack->e.file, _estack->e.line );
        ErrorStack *tmp = _estack;
        _estack = _estack->next;
        free(tmp);
    }
}

#endif // ERR_H
