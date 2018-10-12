// @file
// @brief This file is marvelous.

#ifndef ERR_C
#define ERR_C

#include <stdlib.h>
#include <stdio.h>
#include "err.h"

static ErrorStack *_estack = NULL;

#define perr(errmsg) {                                                  \
        Err e = { .msg = errmsg, .file = __FILE__, .line = __LINE__ };  \
        pushErr(e);                                                     \
    };


void
pushErr(Err e)
{ 
    ErrorStack *stk = (ErrorStack*)malloc(sizeof(ErrorStack));
    stk->e = e;
    stk->next = _estack;
    _estack = stk;
}
    
void
dumpStack()
{
    if (_estack) printf(" -- ERROR STACK --\n");
    while (_estack) {
        printf(" %s (%s, %d)\n", _estack->e.msg, _estack->e.file, _estack->e.line );
        ErrorStack *tmp = _estack;
        _estack = _estack->next;
        free(tmp);
    }
}



#endif // ERR_C
