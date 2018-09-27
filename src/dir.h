#ifndef DIR_H
#define DIR_H

typedef enum { N = 0,
               E = 1,
               S = 2,
               W = 3 } Dir;

// get the opposite direction
Dir dir_opposite(Dir d);

#endif // DIR_H


