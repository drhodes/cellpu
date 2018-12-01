#ifndef GUI_H
#define GUI_H

typedef struct Gui {
    Term *term;
} Gui;




*Gui newGui() {}
bool guiProcessEvent)(struct Gui*, SDL_Event*);



#endif // GUI_H
